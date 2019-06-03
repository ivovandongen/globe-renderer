#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace {

// Default camera values
constexpr float YAW = -90.0f;
constexpr float PITCH = 0.0f;
constexpr float ZOOM = 45.0f;

}  // namespace

namespace glbr {
namespace renderer {

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    inline void move(const glm::vec3& delta) { _position += delta; }

    void move(CameraMovement, float delta);

    inline void zoom(float offset) { _zoom += offset; }

    void orientation(float pitchOffset, float yawOffset, bool constrainPitch = true);

    // Const interface

    glm::mat4 viewMatrix() const;

    inline float zoom() const { return _zoom; }

    inline void position(const glm::vec3& position) { _position = position; }

    inline const glm::vec3& position() const { return _position; }

    inline const glm::vec3& front() const { return _front; }

private:
    void updateCameraVectors();

private:
    // Camera Attributes
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;

    // Euler Angles
    float _yaw;
    float _pitch;

    // Camera options
    float _zoom;
};

}  // namespace renderer
}  // namespace glbr