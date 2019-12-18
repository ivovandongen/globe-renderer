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

    const glm::vec3 target() const { return target_; }

private:
    renderer::Camera &camera_;
    renderer::GraphicsWindow &window_;

    // The constant target vector
    glm::vec3 target_;

    // In order to calculate absolute rotations
    renderer::Camera home_;

    // Mouse move state
    bool firstMove_ = true;
    float lastX_ = 0, lastY_ = 0;
};

}  // namespace scene
}  // namespace glbr