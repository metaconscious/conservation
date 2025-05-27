//
// Created by user on 5/23/25.
//

#include "utilities/Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace csv
{
    Camera::Camera(const float left,
                   const float right,
                   const float bottom,
                   const float top,
                   const float nearPlane,
                   const float farPlane) noexcept
        : m_position(0.0f, 0.0f, 3.0f)
        , m_target(0.0f, 0.0f, 0.0f)
        , m_up(0.0f, 1.0f, 0.0f)
        , m_left(left)
        , m_right(right)
        , m_bottom(bottom)
        , m_top(top)
        , m_near(nearPlane)
        , m_far(farPlane)
    {
        updateProjectionMatrix();
    }

    glm::mat4 Camera::getModelMatrix() const noexcept
    {
        return { 1.0f }; // Identity matrix as default model matrix
    }

    glm::mat4 Camera::getViewMatrix() const noexcept
    {
        return glm::lookAt(m_position, m_target, m_up);
    }

    glm::mat4 Camera::getProjectionMatrix() const noexcept
    {
        return m_projectionMatrix;
    }

    void Camera::setPosition(const glm::vec3& position) noexcept
    {
        m_position = position;
    }

    void Camera::setTarget(const glm::vec3& target) noexcept
    {
        m_target = target;
    }

    void Camera::setUp(const glm::vec3& up) noexcept
    {
        m_up = up;
    }

    void Camera::setOrthographicProjection(
        const float left,
        const float right,
        const float bottom,
        const float top,
        const float nearPlane,
        const float farPlane) noexcept
    {
        m_left = left;
        m_right = right;
        m_bottom = bottom;
        m_top = top;
        m_near = nearPlane;
        m_far = farPlane;
        updateProjectionMatrix();
    }

    void Camera::updateProjectionMatrix() noexcept
    {
        m_projectionMatrix = glm::ortho(m_left, m_right, m_bottom, m_top, m_near, m_far);
    }

    CameraSystem::CameraSystem(GLFWwindow* window)
        : m_window(window)
        , m_camera(std::make_unique<Camera>())
    {
        // Set up window resize callback
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int width, int height)
        {
            const auto* cameraSys = static_cast<CameraSystem*>(glfwGetWindowUserPointer(win));
            cameraSys->onWindowResize(width, height);
        });

        // Initialize with current window size
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        onWindowResize(width, height);
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    void CameraSystem::update() noexcept
    {
        // This method can be expanded to include camera movement, zoom, etc.
    }

    Camera& CameraSystem::getCamera() noexcept
    {
        return *m_camera;
    }

    const Camera& CameraSystem::getCamera() const noexcept
    {
        return *m_camera;
    }

    void CameraSystem::onWindowResize(const int width, const int height) const noexcept
    {
        // Update viewport
        glViewport(0, 0, width, height);

        // Update camera projection to maintain aspect ratio
        const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        constexpr float orthoHeight = 2.0f;
        const float orthoWidth = orthoHeight * aspectRatio;

        m_camera->setOrthographicProjection(
            -orthoWidth / 2.0f, orthoWidth / 2.0f,
            -orthoHeight / 2.0f, orthoHeight / 2.0f,
            0.1f, 100.0f
        );
    }
} // lgl
