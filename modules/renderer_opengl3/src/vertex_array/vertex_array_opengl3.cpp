#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

#include <glbr/renderer/opengl3/context/context_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

VertexArrayOpenGL3::VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3> context) : _context(std::move(context)) {
    GL_VERIFY(glGenVertexArrays(1, &_id));
}

VertexArrayOpenGL3::VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3> context,
                                       std::unique_ptr<IndexBufferOpenGL3> buffer)
    : _context(std::move(context)), _indexBuffer(std::move(buffer)) {
    GL_VERIFY(glGenVertexArrays(1, &_id));
}

VertexArrayOpenGL3::~VertexArrayOpenGL3() {
    GL_VERIFY(glDeleteVertexArrays(1, &_id));
}

void VertexArrayOpenGL3::clean(const Pipeline &pipeline) {
    _attributes.clean(pipeline.vertexAttributeBindings());
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

void VertexArrayOpenGL3::bind() {
    _context->set(shared_from_this());
}

void VertexArrayOpenGL3::unbind() {
    _context->set(nullptr);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
