#pragma once

#include <glbr/core/size.hpp>
#include "camera.hpp"

namespace glbr {
namespace renderer {

class SceneState {
public:
    SceneState(float width, float height, float pixelRatio = 1);

    void viewport(float width, float height, float pixelRatio = 1);

    core::Size2D<float> viewport() const { return {_width, _height}; }

    Camera& camera() { return _camera; };

    const Camera& camera() const { return _camera; };

    void modelMatrix(const glm::mat4& modelMatrix) { _modelMatrix = modelMatrix; }

    const glm::mat4& modelMatrix() const { return _modelMatrix; }

    glm::mat4 projectionMatrix() const;

    float pixelRatio() const { return pixelRatio_; }

private:
    Camera _camera;
    float _width;
    float _height;
    float pixelRatio_;
    glm::mat4 _modelMatrix;
};

}  // namespace renderer
}  // namespace glbr