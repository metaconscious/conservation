//
// Created by user on 5/23/25.
//

#ifndef CONSERVATION_UTILITIES_CAMERA_H
#define CONSERVATION_UTILITIES_CAMERA_H

#include <memory>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

namespace csv
{
    class Camera
    {
    public:
        explicit Camera(float left = -1.0f,
                        float right = 1.0f,
                        float bottom = -1.0f,
                        float top = 1.0f,
                        float nearPlane = 0.1f,
                        float farPlane = 100.0f) noexcept;

        [[nodiscard]] glm::mat4 getModelMatrix() const noexcept;

        [[nodiscard]] glm::mat4 getViewMatrix() const noexcept;

        [[nodiscard]] glm::mat4 getProjectionMatrix() const noexcept;

        void setPosition(const glm::vec3& position) noexcept;

        void setTarget(const glm::vec3& target) noexcept;

        void setUp(const glm::vec3& up) noexcept;

        void setOrthographicProjection(float left,
                                       float right,
                                       float bottom,
                                       float top,
                                       float nearPlane,
                                       float farPlane) noexcept;

    private:
        void updateProjectionMatrix() noexcept;

        glm::vec3 m_position;
        glm::vec3 m_target;
        glm::vec3 m_up;

        float m_left;
        float m_right;
        float m_bottom;
        float m_top;
        float m_near;
        float m_far;

        glm::mat4 m_projectionMatrix{};
    };

    class CameraSystem
    {
    public:
        explicit CameraSystem(GLFWwindow* window);

        void update() noexcept;

        [[nodiscard]] Camera& getCamera() noexcept;

        [[nodiscard]] const Camera& getCamera() const noexcept;

    private:
        void onWindowResize(int width, int height) const noexcept;

        GLFWwindow* m_window;
        std::unique_ptr<Camera> m_camera;
    };
} // lgl

#endif //CONSERVATION_UTILITIES_CAMERA_H
