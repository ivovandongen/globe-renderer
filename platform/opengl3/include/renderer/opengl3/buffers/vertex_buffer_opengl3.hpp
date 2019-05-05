#pragma once

#include <renderer/buffers/vertex_buffer.hpp>
#include <renderer/opengl3/buffers/buffer_opengl3.hpp>

namespace renderer {
namespace opengl3 {

class VertexBufferOpenGL3 : private BufferOpenGL3, public VertexBuffer {
public:
    VertexBufferOpenGL3(BufferHint usageHint, unsigned int sizeInBytes);

    ~VertexBufferOpenGL3() override = default;

    void bind() override { BufferOpenGL3::bind(); }

    void upload(void* data) override { BufferOpenGL3::upload(data); }

    unsigned int size() override { return BufferOpenGL3::size(); }
};

}  // namespace opengl3
}  // namespace renderer