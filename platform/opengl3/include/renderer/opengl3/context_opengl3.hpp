#pragma once

#include <renderer/buffers/index_buffer.hpp>
#include <renderer/buffers/vertex_buffer.hpp>
#include <renderer/context.hpp>
#include <renderer/graphics_window.hpp>
#include <renderer/vertex_array/vertex_array.hpp>

namespace renderer {
namespace opengl3 {

class ContextOpenGL3 : public Context {
public:
    explicit ContextOpenGL3(const GraphicsWindow &);

    ~ContextOpenGL3() override = default;

    void resize(int width, int height) override;

    void makeCurrent() const override;

    std::unique_ptr<VertexArray> createVertexArray() override;

    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) override;

    std::unique_ptr<IndexBuffer> createIndexBuffer(BufferHint usageHint, int sizeInBytes) override;

    void clear(const ClearState &) override;

    void draw(const DrawState &) override;

private:
    const GraphicsWindow &_window;
    ClearState _clearState;
};

}  // namespace opengl3
}  // namespace renderer