#pragma once

#include <glbr/renderer/buffers/buffer_hint.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

enum class BufferTarget { ArrayBuffer, ElementArrayBuffer };

class BufferOpenGL3 {
public:
    BufferOpenGL3(BufferTarget type, ::glbr::renderer::BufferHint usageHint, unsigned int sizeInBytes);

    virtual ~BufferOpenGL3();

    inline void bind() { GL_VERIFY(glBindBuffer(_target, _id)); }

    inline void upload(void* data) { GL_VERIFY(glBufferData(_target, _size, data, _usage)); }

    inline unsigned int size() { return _size; }

private:
    GLuint _id{0};
    GLenum _target;
    GLenum _usage;
    unsigned int _size;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr