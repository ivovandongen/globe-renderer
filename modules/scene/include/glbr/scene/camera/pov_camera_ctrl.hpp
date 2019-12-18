#pragma once

#include <glbr/core/events/event_handler.hpp>
#include <glbr/input/input.hpp>
#include <glbr/renderer/scene/camera.hpp>

#include <glm/vec3.hpp>

namespace glbr {
namespace scene {

class POVCameraController : public core::EventHandler {
public:
    POVCameraController(renderer::Camera &camera, input::Input &, float yaw = -90.0f, float pitch = 0.0f);

    void operator()(core::Event &event) override;

    void orientation(float pitch, float yaw, bool constrainPitch = true);

private:
    void updateCameraVectors();

private:
    input::Input &input_;
    renderer::Camera &camera_;

    // Euler angles used as input to calculate vectors
    float yaw_;
    float pitch_;

    // Mouse move state
    bool firstMove_ = true;
    float lastX_ = 0, lastY_ = 0;
};

}  // namespace scene
}  // namespace glbr