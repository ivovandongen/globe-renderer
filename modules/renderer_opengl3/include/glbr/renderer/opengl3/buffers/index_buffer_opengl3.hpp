#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/opengl3/buffers/buffer_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class IndexBufferOpenGL3 : private BufferOpenGL3, public IndexBuffer {
public:
    IndexBufferOpenGL3(IndexBufferType type, BufferHint usageHint, uint32_t count);

    ~IndexBufferOpenGL3() override = default;

    IndexBufferType type() override { return type_; }

    void bind() override { BufferOpenGL3::bind(); }

    void upload(const void* data) override { BufferOpenGL3::upload(data); }

    void upload(const void* data, uint32_t count) override;

    uint32_t count() const override { return count_; }

private:
    uint32_t count_;
    IndexBufferType type_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr