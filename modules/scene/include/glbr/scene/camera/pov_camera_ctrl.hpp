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
    input::Input &_input;
    renderer::Camera &_camera;

    // Euler angles used as input to calculate vectors
    float _yaw;
    float _pitch;

    // Mouse move state
    bool firstMove = true;
    float lastX = 0, lastY = 0;
};

}  // namespace scene
}  // namespace glbr