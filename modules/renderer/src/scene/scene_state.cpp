#include <glbr/renderer/scene/scene_state.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace glbr {
namespace renderer {

SceneState::SceneState(float width, float height)
    : _camera(Camera()), _width(width), _height(height), _modelMatrix(glm::mat4(1)) {}

glm::mat4 SceneState::projectionMatrix() const {
    // TODO hardcoded FOV
    return glm::perspective(glm::radians(_camera.zoom()), _width / _height, 0.1f, 100.0f);
}
void SceneState::viewport(float width, float height) {
    _width = width;
    _height = height;
}

}  // namespace renderer
}  // namespace glbr