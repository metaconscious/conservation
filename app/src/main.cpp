#include <algorithm>
#include <cmath>
#include <concepts>
#include <print>
#include <ranges>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "utilities/ShaderProgram.h"

constexpr auto INITIAL_WINDOW_WIDTH{ 800 };
constexpr auto INITIAL_WINDOW_HEIGHT{ 600 };

// Generate circle vertices
template<std::floating_point T, std::unsigned_integral U, std::size_t Segments>
constexpr auto generateCircle(const T radius)
{
    // Vertices: center point + Segments points on circumference, each with (x,y) coordinates
    std::array<T, 3 * (Segments + 1)> vertices{};
    // Indices: Segments triangles, each with 3 vertex indices
    std::array<U, 3 * Segments> indices{};

    // Center vertex (v0)
    vertices[0] = 0;
    vertices[1] = 0;
    vertices[2] = 0;

    // Generate vertices on the circumference
    for (std::size_t i{ 0 }; i < Segments; ++i)
    {
        const auto angle{ static_cast<T>(2) * std::numbers::pi_v<T> * static_cast<T>(i) / static_cast<T>(Segments) };
        const auto index{ 3 * (i + 1) };

        vertices[index] = radius * std::cos(angle); // x coordinate
        vertices[index + 1] = radius * std::sin(angle); // y coordinate
        vertices[index + 2] = 0; // z coordinate
    }

    // Generate triangle indices
    // Each triangle connects the center (v0) with two adjacent vertices on the circumference
    for (std::size_t i{ 0 }; i < Segments; ++i)
    {
        std::size_t index{ 3 * i };

        indices[index] = 0; // Center vertex
        indices[index + 1] = i + 1; // Current circumference vertex
        indices[index + 2] = (i + 1) % Segments + 1; // Next circumference vertex (wraps around)
    }

    return std::make_pair(vertices, indices);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    const auto window{
        glfwCreateWindow(
            INITIAL_WINDOW_WIDTH,
            INITIAL_WINDOW_HEIGHT,
            "Conservation",
            nullptr,
            nullptr
        )
    };

    if (window == nullptr)
    {
        std::println(stderr, "Failed to create GLFW window.");
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::println(stderr, "Failed to initialize GLAD.");
        return EXIT_FAILURE;
    }

    glfwSetFramebufferSizeCallback(
        window,
        [](GLFWwindow*, const int width, const int height) -> void
        {
            glViewport(0, 0, width, height);
        }
    );

    constexpr auto segmentSize{ 100 };
//    const auto [vertices, indices]{ generateCircle<float, GLuint, segmentSize>(0.5f) };
    std::array vertices{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    const auto circleShader{ csv::ShaderProgram::load("shaders/circle.vert", "shaders/circle.frag") };

    GLuint vertexArrayObject{};
    glGenVertexArrays(1, &vertexArrayObject);

    GLuint vertexBufferObject{};
    glGenBuffers(1, &vertexBufferObject);

//    GLuint elementBufferObject{};
//    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(vertexBufferObject,
                 vertices.size() * sizeof(std::ranges::range_value_t<decltype(vertices)>),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(std::ranges::range_value_t<decltype(vertices)>),
                          nullptr);
    glEnableVertexAttribArray(0);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
//    glBufferData(elementBufferObject,
//                 indices.size() * sizeof(std::ranges::range_value_t<decltype(indices)>),
//                 indices.data(),
//                 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        circleShader.use();
        glBindVertexArray(vertexArrayObject);
        circleShader.setUniform("model", glm::mat4(1.0f));
        circleShader.setUniform("view", glm::mat4(1.0f));
        circleShader.setUniform("projection", glm::mat4(1.0f));
//        glDrawElements(GL_TRIANGLES,
//                       indices.size(),
//                       GL_UNSIGNED_INT,
//                       nullptr);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);

    glfwTerminate();

    return 0;
}
