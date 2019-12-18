#include <glbr/renderer/opengl3/buffers/buffer_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

#include <cassert>

namespace {

constexpr GLenum convert(const glbr::renderer::opengl3::BufferTarget& target) {
    using namespace glbr::renderer::opengl3;
    switch (target) {
        case BufferTarget::ArrayBuffer:
            return GL_ARRAY_BUFFER;
        case BufferTarget::ElementArrayBuffer:
            return GL_ELEMENT_ARRAY_BUFFER;
        default:
            assert(false);
            return 0;
    }
}

constexpr GLenum convert(const glbr::renderer::BufferHint& hint) {
    using namespace glbr::renderer;
    switch (hint) {
        case BufferHint::StreamDraw:
            return GL_STREAM_DRAW;
        case BufferHint::StreamRead:
            return GL_STREAM_READ;
        case BufferHint::StreamCopy:
            return GL_STREAM_COPY;
        case BufferHint::StaticDraw:
            return GL_STATIC_DRAW;
        case BufferHint::StaticRead:
            return GL_STATIC_READ;
        case BufferHint::StaticCopy:
            return GL_STATIC_COPY;
        case BufferHint::DynamicDraw:
            return GL_DYNAMIC_DRAW;
        case BufferHint::DynamicRead:
            return GL_DYNAMIC_READ;
        case BufferHint::DynamicCopy:
            return GL_DYNAMIC_COPY;
        default:
            assert(false);
            return 0;
    }
}
}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

BufferOpenGL3::BufferOpenGL3(BufferTarget type, BufferHint usageHint)
    : target_(convert(type)), usage_(convert(usageHint)), size_(0) {
    GL_VERIFY(glGenBuffers(1, &id_));
}

BufferOpenGL3::BufferOpenGL3(BufferTarget type, BufferHint usageHint, unsigned int sizeInBytes)
    : target_(convert(type)), usage_(convert(usageHint)), size_(sizeInBytes) {
    GL_VERIFY(glGenBuffers(1, &id_));
}

BufferOpenGL3::~BufferOpenGL3() {
    GL_VERIFY(glDeleteBuffers(1, &id_));
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr