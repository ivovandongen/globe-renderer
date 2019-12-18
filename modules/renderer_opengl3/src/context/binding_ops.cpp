#include <glbr/renderer/opengl3/context/binding_ops.hpp>

#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

void BindingOp<PipelineOpenGL3>::Apply(const std::shared_ptr<PipelineOpenGL3>& val) {
    val->bind();
}

void BindingOp<VertexArrayOpenGL3>::Apply(const std::shared_ptr<VertexArrayOpenGL3>& val) {
    if (!val) {
        GL_VERIFY(glBindVertexArray(0));
    } else {
        GL_VERIFY(glBindVertexArray(val->id()));
    }
}

void BindingOp<ActiveTextureUnitOpenGL3>::Apply(const std::shared_ptr<ActiveTextureUnitOpenGL3>& val) {
    if (!val) {
        GL_VERIFY(glActiveTexture(GL_TEXTURE0));
    } else {
        GL_VERIFY(glActiveTexture(GL_TEXTURE0 + val->index()));
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr