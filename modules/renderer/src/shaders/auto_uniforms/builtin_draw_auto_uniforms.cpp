#include <glbr/renderer/shaders/auto_uniforms/builtin_draw_auto_uniforms.hpp>

namespace glbr {
namespace renderer {

DrawAutoUniform ModelMatrixDrawAutoFactory::operator()(Uniform& uniform) {
    return [&uniform](const Context&, const DrawState&, const SceneState& sceneState) {
        uniform = sceneState.modelMatrix();
    };
}

DrawAutoUniform ViewMatrixDrawAutoFactory::operator()(Uniform& uniform) {
    return [&uniform](const Context&, const DrawState&, const SceneState& sceneState) {
        uniform = sceneState.camera().viewMatrix();
    };
}

DrawAutoUniform ProjectionMatrixDrawAutoFactory::operator()(Uniform& uniform) {
    return [&uniform](const Context&, const DrawState&, const SceneState& sceneState) {
        uniform = sceneState.projectionMatrix();
    };
}

DrawAutoUniform ModelViewProjectionMatrixDrawAutoFactory::operator()(Uniform& uniform) {
    return [&uniform](const Context&, const DrawState&, const SceneState& sceneState) {
        uniform = sceneState.projectionMatrix() * sceneState.camera().viewMatrix() * sceneState.modelMatrix();
    };
}

}  // namespace renderer
}  // namespace glbr