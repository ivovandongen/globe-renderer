#pragma once

#include <glbr/core/size.hpp>
#include "camera.hpp"

namespace glbr {
namespace renderer {

class SceneState {
public:
    SceneState(float width, float height);

    void viewport(float width, float height);

    core::Size2D<float> viewport() const { return {_width, _height}; }

    Camera& camera() { return _camera; };

    const Camera& camera() const { return _camera; };

    void modelMatrix(const glm::mat4& modelMatrix) { _modelMatrix = modelMatrix; }

    const glm::mat4& modelMatrix() const { return _modelMatrix; }

    glm::mat4 projectionMatrix() const;

private:
    Camera _camera;
    float _width;
    float _height;
    glm::mat4 _modelMatrix;
};

}  // namespace renderer
}  // namespace glbr