#include <glbr/renderer/opengl3/buffers/index_buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

inline static const constexpr size_t sizeOf(IndexBufferType type) {
    switch (type) {
        case IndexBufferType::U_SHORT:
            return sizeof(ushort);
        case IndexBufferType::U_INT:
            return sizeof(uint32_t);
    }
}

IndexBufferOpenGL3::IndexBufferOpenGL3(IndexBufferType type, BufferHint usageHint, uint32_t count)
    : BufferOpenGL3(BufferTarget::ElementArrayBuffer, usageHint, count * sizeOf(type)), _type(type), _count(count) {}

void IndexBufferOpenGL3::upload(const void* data, uint32_t count) {
    _count = count;
    BufferOpenGL3::upload(data, count * sizeOf(_type));
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr