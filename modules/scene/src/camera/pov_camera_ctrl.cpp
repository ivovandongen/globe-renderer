#include <glbr/scene/camera/pov_camera_ctrl.hpp>

#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>

#include <glm/glm.hpp>

namespace glbr {
namespace scene {

POVCameraController::POVCameraController(renderer::Camera &camera, input::Input &input, float yaw, float pitch)
    : _camera(camera), _input(input), _yaw(yaw), _pitch(pitch) {
    updateCameraVectors();
}

/**
 * Set euler angles and update camera vectors accordingly
 */
void POVCameraController::orientation(float pitch, float yaw, bool constrainPitch) {
    _yaw += yaw;
    _pitch += pitch;

    if (constrainPitch) {
        std::max(-89.f, std::min(pitch, 89.f));
    }

    updateCameraVectors();
}

/**
 * Update camera vectors from Euler angles
 */
void POVCameraController::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    front.y = sin(glm::radians(_pitch));
    front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
    _camera.front(glm::normalize(front));
}

/**
 * Input event handling
 */
void POVCameraController::operator()(core::Event &event) {
    logging::debug("Event: {}", event.str());
    core::EventDispatcher d(event);

    using namespace glbr::input;
    using namespace glbr::renderer;

    // Move the view around
    d.dispatch<KeyEvent>([&](KeyEvent &event) {
        if (event.state() == KeyState::RELEASE) return false;

        const float delta = 1. / 20;

        switch (event.keyCode()) {
            case KeyCode::KEY_LEFT:
            case KeyCode ::KEY_A:
                _camera.move(CameraMovement::LEFT, delta);
                return true;
            case KeyCode::KEY_RIGHT:
            case KeyCode ::KEY_D:
                _camera.move(CameraMovement::RIGHT, delta);
                return true;
            case KeyCode::KEY_UP:
            case KeyCode ::KEY_W:
                _camera.move(CameraMovement::FORWARD, delta);
                return true;
            case KeyCode::KEY_DOWN:
            case KeyCode ::KEY_S:
                _camera.move(CameraMovement::BACKWARD, delta);
                return true;
            default:
                return false;
        }
    });

    // Zoom on scroll
    d.dispatch<MouseScrollEvent>([&](MouseScrollEvent &event) {
        if (event.offsetY() != 0) {
            _camera.zoomBy(event.offsetY());
            return true;
        }
        return false;
    });

    // Orient the camera with the mouse when alt is held
    d.dispatch<MouseMoveEvent>([&](MouseMoveEvent &event) {
        if (_input.keyState(KeyCode::KEY_LEFT_ALT) != KeyState::PRESS) {
            firstMove = true;
            return false;
        }

        if (firstMove) {
            lastX = event.x();
            lastY = event.y();
            firstMove = false;
            return true;
        }

        double xoffset = event.x() - lastX;
        double yoffset = lastY - event.y();
        lastX = event.x();
        lastY = event.y();

        const float sensitivity = .1;
        orientation(yoffset * sensitivity, xoffset * sensitivity);

        return true;
    });
}

}  // namespace scene
}  // namespace glbr