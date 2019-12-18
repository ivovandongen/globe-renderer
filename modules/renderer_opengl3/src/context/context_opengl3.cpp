#include <glbr/renderer/opengl3/context/context_opengl3.hpp>

#include <glbr/renderer/clear_state.hpp>
#include <glbr/renderer/opengl3/buffers/vertex_buffer_opengl3.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

ContextOpenGL3::ContextOpenGL3(const GraphicsWindow &window)
    : window_(window),
      clearState_(),
      renderState_(){

      };

void ContextOpenGL3::makeCurrent() const {
    window_.makeContextCurrent();
}

void ContextOpenGL3::draw(core::geometry::PrimitiveType primitiveType,
                          const DrawState &drawState,
                          const SceneState &sceneState,
                          uint32_t offset) {
    // Apply render state
    renderState_ = drawState.renderState;
    // Update clear state
    clearState_ = drawState.renderState;

    // Apply programmable state
    pipeline_ = std::dynamic_pointer_cast<PipelineOpenGL3>(drawState.pipeline);
    vertexArray_ = std::dynamic_pointer_cast<VertexArrayOpenGL3>(drawState.vertexArray);

    vertexArray_->clean(*pipeline_);
    pipeline_->clean(*this, drawState, sceneState);

    // Update the texture units
    textureUnits_.clean(*this);

    if (drawState.vertexArray->indexBuffer()) {
        GL_VERIFY(glDrawElements(toPrimitiveType(primitiveType),
                                 drawState.vertexArray->indexBuffer()->count(),
                                 toIndexBufferType(drawState.vertexArray->indexBuffer()->type()),
                                 (const void *)intptr_t(offset)));
    } else {
        assert(false);
        // TODO GL_VERIFY(glDrawArrays(GL_TRIANGLES, 0, state.vertexBu));
    }
}

void ContextOpenGL3::clear(const ClearState &state) {
    // Update clear state
    clearState_ = state;

    // Update render state
    renderState_ = state;

    // Clear
    GL_VERIFY(glClear(toClearBitfield(state.buffers)));
}

void ContextOpenGL3::viewport(int width, int height) {
    GL_VERIFY(glViewport(0, 0, width, height));

    // Make sure to call the superclass implementation
    Context::viewport(width, height);
}

std::shared_ptr<VertexArray> ContextOpenGL3::createVertexArray() {
    return std::make_shared<VertexArrayOpenGL3>(shared_from_this());
}

std::unique_ptr<VertexBuffer> ContextOpenGL3::createVertexBuffer(BufferHint usageHint, int sizeInBytes) const {
    return std::make_unique<VertexBufferOpenGL3>(usageHint, sizeInBytes);
}

std::unique_ptr<IndexBuffer> ContextOpenGL3::createIndexBuffer(IndexBufferType type,
                                                               BufferHint usageHint,
                                                               uint32_t count) const {
    return std::make_unique<IndexBufferOpenGL3>(type, usageHint, count);
}

Device &ContextOpenGL3::device() {
    return DeviceOpenGL3::Instance();
}

const Device &ContextOpenGL3::device() const {
    return DeviceOpenGL3::Instance();
}

void ContextOpenGL3::activeTextureUnit(const TextureUnitOpenGL3 &unit) {
    activeTextureUnit_ = std::make_shared<ActiveTextureUnitOpenGL3>(unit.index());
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
