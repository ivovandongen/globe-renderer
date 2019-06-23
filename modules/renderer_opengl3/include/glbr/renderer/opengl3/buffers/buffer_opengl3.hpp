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
    BufferOpenGL3(BufferTarget type, BufferHint usageHint);

    BufferOpenGL3(BufferTarget type, ::glbr::renderer::BufferHint usageHint, unsigned int sizeInBytes);

    virtual ~BufferOpenGL3();

    inline void bind() const { GL_VERIFY(glBindBuffer(_target, _id)); }

    inline void upload(const void* data) {
        assert(_size > 0);
        GL_VERIFY(glBufferData(_target, _size, data, _usage));
    }

    inline void upload(const void* data, uint32_t size) {
        _size = size;
        upload(data);
    }

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