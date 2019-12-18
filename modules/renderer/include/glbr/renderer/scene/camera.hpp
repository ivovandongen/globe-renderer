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

    inline void zoom(float zoom) { zoom_ = std::max(zoom, 0.f); }

    inline void zoomBy(float offset) { zoom(zoom_ + offset); }

    inline void position(const glm::vec3& position) { position_ = position; }

    inline void front(const glm::vec3& front) {
        front_ = glm::normalize(front);
        updateDerivedVectors();
    }

    // Const interface

    glm::mat4 viewMatrix() const;

    inline float zoom() const { return zoom_; }

    inline const glm::vec3& position() const { return position_; }

    inline const glm::vec3& front() const { return front_; }

    inline const glm::vec3& right() const { return right_; }

    inline const glm::vec3& up() const { return up_; }

    inline std::string str() const {
        std::stringstream ss;
        ss << "camera[";
        ss << "position: (" << position_.x << ", " << position_.y << ", " << position_.z << ")";
        ss << " front: (" << front_.x << ", " << front_.y << ", " << front_.z << ")";
        ss << " up: (" << up_.x << ", " << up_.y << ", " << up_.z << ")";
        ss << " right: (" << right_.x << ", " << right_.y << ", " << right_.z << ")";
        ss << "]";
        return ss.str();
    }

private:
    void updateDerivedVectors();

private:
    // Camera Attributes
    glm::vec3 position_;
    glm::vec3 front_;
    glm::vec3 up_;
    glm::vec3 right_;

    // Reference for cross product calculation
    glm::vec3 worldUp_;

    // Camera options
    float zoom_{45.0f};
};

}  // namespace renderer
}  // namespace glbr