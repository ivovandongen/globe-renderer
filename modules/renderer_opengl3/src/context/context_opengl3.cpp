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
    : _window(window),
      _clearState(),
      _renderState(){

      };

void ContextOpenGL3::makeCurrent() const {
    _window.makeContextCurrent();
}

void ContextOpenGL3::draw(core::geometry::PrimitiveType primitiveType, const DrawState &drawState,
                          const SceneState &sceneState) {
    // Apply render state
    _renderState = drawState.renderState;
    // Update clear state
    _clearState = drawState.renderState;

    // Apply programmable state
    _pipeline = std::dynamic_pointer_cast<PipelineOpenGL3>(drawState.pipeline);
    _vertexArray = std::dynamic_pointer_cast<VertexArrayOpenGL3>(drawState.vertexArray);

    _vertexArray->clean(*_pipeline);
    _pipeline->clean(*this, drawState, sceneState);

    // Update the texture units
    _textureUnits.clean();

    // TODO
    if (drawState.vertexArray->indexBuffer()) {
        // TODO support other index types than uint
        GL_VERIFY(glDrawElements(toPrimitiveType(primitiveType), drawState.vertexArray->indexBuffer()->count(),
                                 GL_UNSIGNED_INT, nullptr));
                                 toIndexBufferType(drawState.vertexArray->indexBuffer()->type()),
                                 nullptr));
    } else {
        assert(false);
        // TODO GL_VERIFY(glDrawArrays(GL_TRIANGLES, 0, state.vertexBu));
    }
}

void ContextOpenGL3::clear(const ClearState &state) {
    // Update clear state
    _clearState = state;

    // Update render state
    _renderState = state;

    // Clear
    GL_VERIFY(glClear(toClearBitfield(state.buffers)));
}

void ContextOpenGL3::viewport(int width, int height) {
    GL_VERIFY(glViewport(0, 0, width, height));

    // Make sure to call the superclass implementation
    Context::viewport(width, height);
}

std::unique_ptr<VertexArray> ContextOpenGL3::createVertexArray() const {
    return std::make_unique<VertexArrayOpenGL3>();
}

std::unique_ptr<VertexBuffer> ContextOpenGL3::createVertexBuffer(BufferHint usageHint, int sizeInBytes) const {
    return std::make_unique<VertexBufferOpenGL3>(usageHint, sizeInBytes);
}

std::unique_ptr<IndexBuffer> ContextOpenGL3::createIndexBuffer(IndexBufferType type, BufferHint usageHint,
                                                               uint32_t count) const {
    return std::make_unique<IndexBufferOpenGL3>(type, usageHint, count);
}

Device &ContextOpenGL3::device() {
    return DeviceOpenGL3::instance();
}

const Device &ContextOpenGL3::device() const {
    return DeviceOpenGL3::instance();
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
