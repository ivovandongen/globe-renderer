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

    inline void bind() const { GL_VERIFY(glBindBuffer(target_, id_)); }

    inline void upload(const void* data) {
        assert(size_ > 0);
        GL_VERIFY(glBufferData(target_, size_, data, usage_));
    }

    inline void upload(const void* data, uint32_t size) {
        size_ = size;
        upload(data);
    }

    inline unsigned int size() { return size_; }

private:
    GLuint id_{0};
    GLenum target_;
    GLenum usage_;
    unsigned int size_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr