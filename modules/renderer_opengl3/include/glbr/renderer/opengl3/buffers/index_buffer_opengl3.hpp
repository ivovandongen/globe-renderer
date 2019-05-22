#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/opengl3/buffers/buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class IndexBufferOpenGL3 : private BufferOpenGL3, public IndexBuffer {
public:
    IndexBufferOpenGL3(BufferHint usageHint, uint sizeInBytes);

    ~IndexBufferOpenGL3() override = default;

    void bind() override { BufferOpenGL3::bind(); }

    void upload(const void* data) override { BufferOpenGL3::upload(data); }

    uint size() override { return BufferOpenGL3::size(); }
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr