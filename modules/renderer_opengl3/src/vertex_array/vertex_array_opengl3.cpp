#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

#include <glbr/renderer/opengl3/context/context_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

VertexArrayOpenGL3::VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3> context) : context_(std::move(context)) {
    GL_VERIFY(glGenVertexArrays(1, &id_));
}

VertexArrayOpenGL3::VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3> context,
                                       std::unique_ptr<IndexBufferOpenGL3> buffer)
    : context_(std::move(context)), indexBuffer_(std::move(buffer)) {
    GL_VERIFY(glGenVertexArrays(1, &id_));
}

VertexArrayOpenGL3::~VertexArrayOpenGL3() {
    GL_VERIFY(glDeleteVertexArrays(1, &id_));
}

void VertexArrayOpenGL3::clean(const Pipeline &pipeline) {
    attributes_.clean(pipeline.vertexAttributeBindings());
}

IndexBufferOpenGL3 *VertexArrayOpenGL3::indexBuffer() {
    return indexBuffer_.get();
}

void VertexArrayOpenGL3::indexBuffer(std::shared_ptr<IndexBuffer> buffer) {
    indexBuffer_ = std::dynamic_pointer_cast<IndexBufferOpenGL3>(buffer);
}

void VertexArrayOpenGL3::add(const std::string &key, VertexBufferAttribute attribute) {
    attributes_[key] = attribute;
}

void VertexArrayOpenGL3::bind() {
    context_->set(shared_from_this());
}

void VertexArrayOpenGL3::unbind() {
    context_->set(nullptr);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
