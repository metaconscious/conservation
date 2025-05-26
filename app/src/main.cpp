#include <print>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

constexpr auto INITIAL_WINDOW_WIDTH{ 800 };
constexpr auto INITIAL_WINDOW_HEIGHT{ 600 };

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


    return 0;
}
