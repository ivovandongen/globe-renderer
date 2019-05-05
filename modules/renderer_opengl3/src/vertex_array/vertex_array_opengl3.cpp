#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

namespace {

GLenum convert(glbr::renderer::VertexAttribute::Type type) {
    using namespace glbr::renderer;
    switch (type) {
        case VertexAttribute::Type::Float:
            return GL_FLOAT;
    }
}

}  // namespace

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

void VertexArrayOpenGL3::bind() {
    GL_VERIFY(glBindVertexArray(_id));

    // TODO separate from bind?
    if (_attributesDirty) {
        for (size_t i = 0; i < _attributes.size(); i++) {
            auto &attrib = _attributes[i];
            auto type = convert(attrib.type());
            glVertexAttribPointer(i, attrib.components(), type, attrib.normalize(), attrib.stride(),
                                  reinterpret_cast<void *>(attrib.offset()));
            glEnableVertexAttribArray(i);
        }
        _attributesDirty = false;
    }
}

void VertexArrayOpenGL3::unbind() {
    GL_VERIFY(glBindVertexArray(0));
}

IndexBufferOpenGL3 *VertexArrayOpenGL3::indexBuffer() {
    return _indexBuffer.get();
}

void VertexArrayOpenGL3::indexBuffer(std::unique_ptr<IndexBuffer> buffer) {
    _indexBuffer.reset(dynamic_cast<IndexBufferOpenGL3 *>(buffer.release()));
}

void VertexArrayOpenGL3::add(VertexAttribute attribute) {
    _attributes.push_back(std::move(attribute));
    _attributesDirty = true;
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
