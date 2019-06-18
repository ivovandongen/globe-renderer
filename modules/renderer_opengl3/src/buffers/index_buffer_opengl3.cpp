#include <glbr/renderer/opengl3/buffers/index_buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

IndexBufferOpenGL3::IndexBufferOpenGL3(BufferHint usageHint, uint32_t count)
    : BufferOpenGL3(BufferTarget::ElementArrayBuffer, usageHint, count * sizeof(uint32_t)), _count(count) {}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr