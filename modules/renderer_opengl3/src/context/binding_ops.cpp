#include <glbr/renderer/opengl3/context/binding_ops.hpp>

#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

void BindingOp<PipelineOpenGL3>::Apply(const PipelineOpenGL3& val) {
    val.bind();
}

void BindingOp<VertexArrayOpenGL3>::Apply(const VertexArrayOpenGL3& val) {
    val.bind();
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr