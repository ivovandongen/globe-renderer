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

OrbitingCameraController::OrbitingCameraController(renderer::Camera& camera, renderer::GraphicsWindow& window,
                                                   glm::vec3 target)
    : _camera(camera), _window(window), _target(target) {
    // Point the camera to the target
    _camera.front(_target - _camera.position());

    // Save the "home" state
    _home = camera;
}

void OrbitingCameraController::rotateBy(float x, float y) {
    // Find rotation axis
    auto yAxis = glm::normalize(_camera.up());
    auto xAxis = glm::normalize(_camera.right());

    // Rotate
    _camera.position(glm::angleAxis(y, yAxis) * glm::angleAxis(x, xAxis) * _camera.position());
    _camera.front(-_camera.position() - _target);
    logging::info("Camera : {}", _camera.str());
}

void OrbitingCameraController::rotation(float x, float y) {
    _camera.position(_home.position());
    _camera.front(_home.front());
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
        if (_window.mouseButtonState(MouseButtonCode::MOUSE_BUTTON_1) != KeyState::PRESS) {
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
        double yoffset = event.y() - lastY;
        lastX = event.x();
        lastY = event.y();

        rotateBy(-core::deg2rad(yoffset / _window.size().height * 100),
                 -core::deg2rad(xoffset / _window.size().width * 100));

        return true;
    });

    d.dispatch<MouseScrollEvent>([&](MouseScrollEvent& event) {
        if (event.offsetY() != 0) {
            _camera.zoomBy(event.offsetY());
            return true;
        }
        return false;
    });
}

}  // namespace scene
}  // namespace glbr