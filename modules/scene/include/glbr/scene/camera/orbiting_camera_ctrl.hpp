#pragma once

#include <glbr/core/events/event_handler.hpp>
#include <glbr/renderer/graphics_window.hpp>
#include <glbr/renderer/scene/camera.hpp>

namespace glbr {
namespace scene {

class OrbitingCameraController : public core::EventHandler {
public:
    OrbitingCameraController(renderer::Camera &, renderer::GraphicsWindow &, glm::vec3 target = glm::vec3(0, 0, 0));

    void rotation(float x, float y);

    void rotateBy(float x, float y);

    void operator()(core::Event &event) override;

    const glm::vec3 target() const { return _target; }

private:
    renderer::Camera &_camera;
    renderer::GraphicsWindow &_window;

    // The constant target vector
    glm::vec3 _target;

    // In order to calculate absolute rotations
    renderer::Camera _home;

    // Mouse move state
    bool firstMove = true;
    float lastX = 0, lastY = 0;
};

}  // namespace scene
}  // namespace glbr