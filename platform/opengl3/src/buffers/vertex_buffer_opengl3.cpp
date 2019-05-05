#include <renderer/opengl3/buffers/vertex_buffer_opengl3.hpp>

namespace renderer {
namespace opengl3 {

VertexBufferOpenGL3::VertexBufferOpenGL3(BufferHint usageHint, unsigned int sizeInBytes)
    : BufferOpenGL3(BufferTarget::ArrayBuffer, usageHint, sizeInBytes) {}

}  // namespace opengl3
}  // namespace renderer