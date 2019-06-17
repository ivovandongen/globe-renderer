#pragma once

#include <glbr/renderer/buffers/vertex_buffer.hpp>
#include <glbr/renderer/opengl3/buffers/buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class VertexBufferOpenGL3 : private BufferOpenGL3, public VertexBuffer {
public:
    VertexBufferOpenGL3(BufferHint usageHint, unsigned int sizeInBytes);

    ~VertexBufferOpenGL3() override = default;

    void bind() const override { BufferOpenGL3::bind(); }

    void upload(const void* data) override { BufferOpenGL3::upload(data); }

    unsigned int size() override { return BufferOpenGL3::size(); }
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr