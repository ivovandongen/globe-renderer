#pragma once

#include <glbr/renderer/shaders/auto_uniforms/draw_auto_uniform_factory.hpp>

namespace glbr {
namespace renderer {

struct ModelMatrixDrawAutoFactory : DrawAutoUniformFactory {
    DrawAutoUniform operator()(Uniform& uniform) override;
};

struct ViewMatrixDrawAutoFactory : DrawAutoUniformFactory {
    DrawAutoUniform operator()(Uniform& uniform) override;
};

struct ProjectionMatrixDrawAutoFactory : DrawAutoUniformFactory {
    DrawAutoUniform operator()(Uniform& uniform) override;
};

struct ModelViewProjectionMatrixDrawAutoFactory : DrawAutoUniformFactory {
    DrawAutoUniform operator()(Uniform& uniform) override;
};

}  // namespace renderer
}  // namespace glbr