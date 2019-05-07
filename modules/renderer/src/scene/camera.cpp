#include <glbr/renderer/scene/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace glbr {
namespace renderer {

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : _front(glm::vec3(0.0f, 0.0f, -1.0f)), _zoom(ZOOM), _position(position), _worldUp(up), _yaw(yaw), _pitch(pitch) {
    updateCameraVectors();
}

glm::mat4 Camera::viewMatrix() {
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _front = glm::normalize(front);

    // Also re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower
    // movement.
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

}  // namespace renderer
}  // namespace glbr