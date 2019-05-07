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

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                    float yaw = YAW, float pitch = PITCH);

    glm::mat4 viewMatrix();

    inline float zoom() const { return _zoom; };

    inline const glm::vec3& position() const { return _position; }

    inline const glm::vec3& front() const { return _front; }

    inline void position(const glm::vec3& position) { _position = position; }

    inline void up(const glm::vec3& up) { _up = up; }

    inline void front(const glm::vec3& front) { _front = front; }

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