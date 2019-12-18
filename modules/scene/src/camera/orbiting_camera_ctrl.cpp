#include <glbr/scene/camera/orbiting_camera_ctrl.hpp>

#include <glbr/core/maths.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>

#include <glm/gtc/constants.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace glbr {
namespace scene {

OrbitingCameraController::OrbitingCameraController(renderer::Camera& camera,
                                                   renderer::GraphicsWindow& window,
                                                   glm::vec3 target)
    : camera_(camera), window_(window), target_(target) {
    // Point the camera to the target
    camera_.front(target - camera.position());

    // Save the "home" state
    home_ = camera_;
}

void OrbitingCameraController::rotateBy(float x, float y) {
    // Find rotation axis
    auto yAxis = glm::normalize(camera_.up());
    auto xAxis = glm::normalize(camera_.right());

    // Rotate
    camera_.position(glm::angleAxis(y, yAxis) * glm::angleAxis(x, xAxis) * camera_.position());
    camera_.front(-camera_.position() - target_);
    logging::info("Camera : {}", camera_.str());
}

void OrbitingCameraController::rotation(float x, float y) {
    camera_.position(home_.position());
    camera_.front(home_.front());
    rotateBy(x, y);
}

void OrbitingCameraController::operator()(core::Event& event) {
    core::EventDispatcher d(event);

    using namespace glbr::input;

    d.dispatch<KeyEvent>([&](KeyEvent& event) {
        if (event.state() == KeyState::RELEASE) {
            return false;
        }

        switch (event.keyCode()) {
            case KeyCode::KEY_UP:
                rotateBy(core::deg2rad(10.), 0);
                return true;
            case KeyCode::KEY_DOWN:
                rotateBy(core::deg2rad(-10.), 0);
                return true;
            case KeyCode::KEY_LEFT:
                rotateBy(0, core::deg2rad(-10.));
                return true;
            case KeyCode::KEY_RIGHT:
                rotateBy(0, core::deg2rad(10.));
                return true;
            case KeyCode::KEY_F:
                rotation(0, core::deg2rad(360.));
                return true;
            case KeyCode::KEY_R:
                rotation(0, 0);
                return true;
            case KeyCode::KEY_D:
                rotation(0, core::deg2rad(90.));
                return true;
            case KeyCode::KEY_G:
                rotation(0, core::deg2rad(-90.));
                return true;
            default:
                return false;
        }
    });

    // Camera pan controls
    d.dispatch<MouseMoveEvent>([&](MouseMoveEvent& event) {
        if (window_.mouseButtonState(MouseButtonCode::MOUSE_BUTTON_1) != KeyState::PRESS) {
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
        double yoffset = event.y() - lastY_;
        lastX_ = event.x();
        lastY_ = event.y();

        rotateBy(-core::deg2rad(yoffset / window_.size().height * 100),
                 -core::deg2rad(xoffset / window_.size().width * 100));

        return true;
    });

    d.dispatch<MouseScrollEvent>([&](MouseScrollEvent& event) {
        if (event.offsetY() != 0) {
            camera_.zoomBy(event.offsetY());
            return true;
        }
        return false;
    });
}

}  // namespace scene
}  // namespace glbr