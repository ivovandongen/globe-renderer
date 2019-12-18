#include <glbr/renderer/scene/scene_state.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace glbr {
namespace renderer {

SceneState::SceneState(float width, float height, float pixelRatio)
    : camera_(Camera()), width_(width), height_(height), pixelRatio_(pixelRatio), modelMatrix_(glm::mat4(1)) {}

glm::mat4 SceneState::projectionMatrix() const {
    // TODO hardcoded FOV
    return glm::perspective(glm::radians(camera_.zoom()), width_ / height_, 0.1f, 100.0f);
}

void SceneState::viewport(float width, float height, float pixelRatio) {
    width_ = width;
    height_ = height;
    pixelRatio_ = pixelRatio;
}

}  // namespace renderer
}  // namespace glbr