#pragma once

#include "camera.hpp"

namespace glbr {
namespace renderer {

class SceneState {
public:
    SceneState(float width, float height);

    void viewport(float width, float height);

    Camera& camera() { return _camera; };

    const Camera& camera() const { return _camera; };

    glm::mat4 projectionMatrix() const;

private:
    Camera _camera;
    float _width;
    float _height;
};

}  // namespace renderer
}  // namespace glbr