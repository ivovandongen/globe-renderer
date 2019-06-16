#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

#include <algorithm>
#include <sstream>

namespace glbr {
namespace renderer {

enum class CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
public:
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    void move(CameraMovement, float delta);

    inline void zoom(float zoom) { _zoom = std::max(zoom, 0.f); }

    inline void zoomBy(float offset) { zoom(_zoom + offset); }

    inline void position(const glm::vec3& position) { _position = position; }

    inline void front(const glm::vec3& front) {
        _front = glm::normalize(front);
        updateDerivedVectors();
    }

    // Const interface

    glm::mat4 viewMatrix() const;

    inline float zoom() const { return _zoom; }

    inline const glm::vec3& position() const { return _position; }

    inline const glm::vec3& front() const { return _front; }

    inline const glm::vec3& right() const { return _right; }

    inline const glm::vec3& up() const { return _up; }

    inline std::string str() const {
        std::stringstream ss;
        ss << "camera[";
        ss << "position: (" << _position.x << ", " << _position.y << ", " << _position.z << ")";
        ss << " front: (" << _front.x << ", " << _front.y << ", " << _front.z << ")";
        ss << " up: (" << _up.x << ", " << _up.y << ", " << _up.z << ")";
        ss << " right: (" << _right.x << ", " << _right.y << ", " << _right.z << ")";
        ss << "]";
        return ss.str();
    }

private:
    void updateDerivedVectors();

private:
    // Camera Attributes
    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;

    // Reference for cross product calculation
    glm::vec3 _worldUp;

    // Camera options
    float _zoom{45.0f};
};

}  // namespace renderer
}  // namespace glbr