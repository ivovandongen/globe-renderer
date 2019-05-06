#include <glbr/renderer/opengl3/buffers/vertex_buffer_opengl3.hpp>
#include <glbr/renderer/opengl3/context_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

ContextOpenGL3::ContextOpenGL3(const GraphicsWindow &window)
    : _window(window),
      _clearState(){

      };

void ContextOpenGL3::makeCurrent() const {
    _window.makeContextCurrent();
}

void ContextOpenGL3::draw(const DrawState &state) {
    // TODO: dirty checking
    state.pipeline.bind();
    state.vertexArray.bind();
    dynamic_cast<VertexArrayOpenGL3 &>(state.vertexArray).clean(state.pipeline);

    // TODO
    if (state.vertexArray.indexBuffer()) {
        // TODO support other index types than uint
        GL_VERIFY(glDrawElements(GL_TRIANGLES, state.vertexArray.indexBuffer()->size(), GL_UNSIGNED_INT, nullptr););
    } else {
        // TODO GL_VERIFY(glDrawArrays(GL_TRIANGLES, 0, state.vertexBu));
    }
}

void ContextOpenGL3::clear(const ClearState &state) {
    // TODO: dirty state

    // Clear color
    if (state.color != _clearState.color) {
        GL_VERIFY(glClearColor(state.color[0], state.color[1], state.color[2], state.color[3]));
        _clearState.color = state.color;
    }

    // TODO: other bits
    GL_VERIFY(glClear(GL_COLOR_BUFFER_BIT));
}

void ContextOpenGL3::resize(int width, int height) {
    GL_VERIFY(glViewport(0, 0, width, height));
}

std::unique_ptr<VertexArray> ContextOpenGL3::createVertexArray() {
    return std::make_unique<VertexArrayOpenGL3>();
}

std::unique_ptr<VertexBuffer> ContextOpenGL3::createVertexBuffer(BufferHint usageHint, int sizeInBytes) {
    return std::make_unique<VertexBufferOpenGL3>(usageHint, sizeInBytes);
}

std::unique_ptr<IndexBuffer> ContextOpenGL3::createIndexBuffer(BufferHint usageHint, int sizeInBytes) {
    return std::make_unique<IndexBufferOpenGL3>(usageHint, sizeInBytes);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
