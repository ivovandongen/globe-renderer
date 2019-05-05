#include <glbr/renderer/opengl3/buffers/index_buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

IndexBufferOpenGL3::IndexBufferOpenGL3(BufferHint usageHint, unsigned int sizeInBytes)
    : BufferOpenGL3(BufferTarget::ElementArrayBuffer, usageHint, sizeInBytes) {}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr