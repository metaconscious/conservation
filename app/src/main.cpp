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
template<std::floating_point T, std::size_t Segments>
constexpr std::array<T, 3 * (Segments + 2)> generateCircle(const T radius)
{
    std::array<T, 3 * (Segments + 2)> vertices{};
    constexpr auto tau{ static_cast<T>(2) * std::numbers::pi_v<T> };

    for (const auto index : std::views::iota(0uz, Segments + 1))
    {
        const auto theta{ tau * static_cast<T>(index) / static_cast<T>(Segments) };
        vertices[3 + index * 3 + 0] = radius * std::cos(theta);
        vertices[3 + index * 3 + 1] = radius * std::sin(theta);
        vertices[3 + index * 3 + 2] = static_cast<T>(0);
    }
    return vertices;
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
    const auto vertices{ generateCircle<float, segmentSize>(0.5f) };

    const auto circleShader{ csv::ShaderProgram::load("shaders/circle.vert", "shaders/circle.frag") };

    GLuint vertexArrayObject{};
    glGenVertexArrays(1, &vertexArrayObject);

    GLuint vertexBufferObject{};
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(vertexArrayObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(std::ranges::range_value_t<decltype(vertices)>) * vertices.size(),
                 vertices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          3 * sizeof(std::ranges::range_value_t<decltype(vertices)>),
                          nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

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
        glDrawArrays(GL_LINES, 0, segmentSize + 2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);

    glfwTerminate();

    return 0;
}
