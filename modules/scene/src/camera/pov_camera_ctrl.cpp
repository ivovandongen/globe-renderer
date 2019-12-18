#include <glbr/scene/camera/pov_camera_ctrl.hpp>

#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>

#include <glm/glm.hpp>

namespace glbr {
namespace scene {

POVCameraController::POVCameraController(renderer::Camera &camera, input::Input &input, float yaw, float pitch)
    : camera_(camera), input_(input), yaw_(yaw), pitch_(pitch) {
    updateCameraVectors();
}

/**
 * Set euler angles and update camera vectors accordingly
 */
void POVCameraController::orientation(float pitch, float yaw, bool constrainPitch) {
    yaw_ += yaw;
    pitch_ += pitch;

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
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    camera_.front(glm::normalize(front));
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
                camera_.move(CameraMovement::LEFT, delta);
                return true;
            case KeyCode::KEY_RIGHT:
            case KeyCode ::KEY_D:
                camera_.move(CameraMovement::RIGHT, delta);
                return true;
            case KeyCode::KEY_UP:
            case KeyCode ::KEY_W:
                camera_.move(CameraMovement::FORWARD, delta);
                return true;
            case KeyCode::KEY_DOWN:
            case KeyCode ::KEY_S:
                camera_.move(CameraMovement::BACKWARD, delta);
                return true;
            default:
                return false;
        }
    });

    // Zoom on scroll
    d.dispatch<MouseScrollEvent>([&](MouseScrollEvent &event) {
        if (event.offsetY() != 0) {
            camera_.zoomBy(event.offsetY());
            return true;
        }
        return false;
    });

    // Orient the camera with the mouse when alt is held
    d.dispatch<MouseMoveEvent>([&](MouseMoveEvent &event) {
        if (input_.keyState(KeyCode::KEY_LEFT_ALT) != KeyState::PRESS) {
            firstMove_ = true;
            return false;
        }

        if (firstMove_) {
            lastX_ = event.x();
            lastY_ = event.y();
            firstMove_ = false;
            return true;
        }

        double xoffset = event.x() - lastX_;
        double yoffset = lastY_ - event.y();
        lastX_ = event.x();
        lastY_ = event.y();

        const float sensitivity = .1;
        orientation(yoffset * sensitivity, xoffset * sensitivity);

        return true;
    });
}

}  // namespace scene
}  // namespace glbr