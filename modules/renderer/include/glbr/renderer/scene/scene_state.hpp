#pragma once

#include <glbr/core/size.hpp>

#include "camera.hpp"

namespace glbr {
namespace renderer {

class SceneState {
public:
    SceneState(float width, float height, float pixelRatio = 1);

    void viewport(float width, float height, float pixelRatio = 1);

    core::Size2D<float> viewport() const { return {width_, height_}; }

    Camera& camera() { return camera_; };

    const Camera& camera() const { return camera_; };

    void modelMatrix(const glm::mat4& modelMatrix) { modelMatrix_ = modelMatrix; }

    const glm::mat4& modelMatrix() const { return modelMatrix_; }

    glm::mat4 projectionMatrix() const;

    float pixelRatio() const { return pixelRatio_; }

private:
    Camera camera_;
    float width_;
    float height_;
    float pixelRatio_;
    glm::mat4 modelMatrix_;
};

}  // namespace renderer
}  // namespace glbr