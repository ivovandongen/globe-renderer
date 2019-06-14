#include <glbr/scene/camera/orbiting_camera_ctrl.hpp>

#include <glbr/core/maths.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>

#include <glm/gtc/constants.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace glbr {
namespace scene {

OrbitingCameraController::OrbitingCameraController(renderer::Camera& camera, input::Input& input, glm::vec3 target)
    : _camera(camera), _input(input), _target(target), _home(camera) {}

void OrbitingCameraController::rotateBy(float x, float y) {
    _camera.position(glm::rotateY(_camera.position(), y));
    _camera.position(glm::rotateX(_camera.position(), x));
    _camera.front(_target - _camera.position());
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
                rotateBy(core::deg2rad(10), 0);
                return true;
            case KeyCode::KEY_DOWN:
                rotateBy(core::deg2rad(-10), 0);
                return true;
            case KeyCode::KEY_LEFT:
                rotateBy(0, core::deg2rad(-10));
                return true;
            case KeyCode::KEY_RIGHT:
                rotateBy(0, core::deg2rad(10));
                return true;
            case KeyCode::KEY_R:
                rotation(0, 0);
                return true;
            default:
                return false;
        }
    });

    // TODO: camera pan controls around world
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