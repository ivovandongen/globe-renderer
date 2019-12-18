#include <glbr/renderer/scene/camera.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include <algorithm>

namespace glbr {
namespace renderer {

Camera::Camera(glm::vec3 position, glm::vec3 up)
    : front_(glm::vec3(0.0f, 0.0f, -1.0f)), position_(position), up_(up), worldUp_(up) {
    updateDerivedVectors();
}

glm::mat4 Camera::viewMatrix() const {
    return glm::lookAt(position_, position_ + front_, up_);
}

void Camera::move(CameraMovement direction, float delta) {
    switch (direction) {
        case CameraMovement::FORWARD:
            position_ += front_ * delta;
            break;
        case CameraMovement::BACKWARD:
            position_ -= front_ * delta;
            break;
        case CameraMovement::LEFT:
            position_ -= right_ * delta;
            break;
        case CameraMovement::RIGHT:
            position_ += right_ * delta;
            break;
    }
}

void Camera::updateDerivedVectors() {
    // Re-calculate the Right and Up vector
    // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in
    // slower movement.
    right_ = glm::normalize(glm::cross(front_, worldUp_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

}  // namespace renderer
}  // namespace glbr