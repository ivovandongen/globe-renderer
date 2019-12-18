#pragma once

#include <glbr/renderer/opengl3/context/binding_state.hpp>

#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/active_texture_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

template <>
struct BindingOp<PipelineOpenGL3> {
    static void Apply(const std::shared_ptr<PipelineOpenGL3>& val);
};

template <>
struct BindingOp<VertexArrayOpenGL3> {
    static void Apply(const std::shared_ptr<VertexArrayOpenGL3>& val);
};

template <>
struct BindingOp<ActiveTextureUnitOpenGL3> {
    static void Apply(const std::shared_ptr<ActiveTextureUnitOpenGL3>& val);
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr