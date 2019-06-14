#include <glbr/renderer/scene/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include <algorithm>

namespace glbr {
namespace renderer {

Camera::Camera(glm::vec3 position, glm::vec3 up)
    : _front(glm::vec3(0.0f, 0.0f, -1.0f)),  _position(position), _up(up), _worldUp(up) {
    updateDerivedVectors();
}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(_position, _position + _front, _up);
}

void Camera::move(CameraMovement direction, float delta) {
    switch (direction) {
        case CameraMovement::FORWARD:
            _position += _front * delta;
            break;
        case CameraMovement::BACKWARD:
            _position -= _front * delta;
            break;
        case CameraMovement::LEFT:
            _position -= _right * delta;
            break;
        case CameraMovement::RIGHT:
            _position += _right * delta;
            break;
    }
}

void Camera::updateDerivedVectors() {
    // Re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in
    // slower movement.
    _right = glm::normalize(glm::cross(_front, _worldUp));
    _up = glm::normalize(glm::cross(_right, _front));
}

}  // namespace renderer
}  // namespace glbr