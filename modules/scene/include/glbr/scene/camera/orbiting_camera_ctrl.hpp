#pragma once

#include <glbr/core/events/event_handler.hpp>
#include <glbr/input/input.hpp>
#include <glbr/renderer/scene/camera.hpp>

namespace glbr {
namespace scene {

class OrbitingCameraController : public core::EventHandler {
public:
    OrbitingCameraController(renderer::Camera &, input::Input &, glm::vec3 target = glm::vec3(0, 0, 0));

    void rotation(float x, float y);

    void rotateBy(float x, float y);

    void operator()(core::Event &event) override;

private:
    renderer::Camera &_camera;
    input::Input &_input;

    glm::vec3 _target;

    // In order to calculate absolute rotations
    renderer::Camera _home;
};

}  // namespace scene
}  // namespace glbr