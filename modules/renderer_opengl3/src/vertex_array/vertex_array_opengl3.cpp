#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

VertexArrayOpenGL3::VertexArrayOpenGL3() {
    GL_VERIFY(glGenVertexArrays(1, &_id));
}

VertexArrayOpenGL3::VertexArrayOpenGL3(std::unique_ptr<IndexBufferOpenGL3> buffer) : _indexBuffer(std::move(buffer)) {
    GL_VERIFY(glGenVertexArrays(1, &_id));
}

VertexArrayOpenGL3::~VertexArrayOpenGL3() {
    GL_VERIFY(glDeleteVertexArrays(1, &_id));
}

void VertexArrayOpenGL3::bind() const {
    GL_VERIFY(glBindVertexArray(_id));
}

void VertexArrayOpenGL3::clean(const Pipeline &pipeline) {
    _attributes.clean(pipeline.vertexAttributeBindings());
}

void VertexArrayOpenGL3::unbind() {
    GL_VERIFY(glBindVertexArray(0));
}

IndexBufferOpenGL3 *VertexArrayOpenGL3::indexBuffer() {
    return _indexBuffer.get();
}

void VertexArrayOpenGL3::indexBuffer(std::shared_ptr<IndexBuffer> buffer) {
    _indexBuffer = std::dynamic_pointer_cast<IndexBufferOpenGL3>(buffer);
}

void VertexArrayOpenGL3::add(const std::string &key, VertexBufferAttribute attribute) {
    _attributes[key] = attribute;
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
