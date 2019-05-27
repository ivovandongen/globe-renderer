#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/buffers/vertex_buffer.hpp>
#include <glbr/renderer/context.hpp>
#include <glbr/renderer/graphics_window.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

#include <glbr/renderer/opengl3/context/render_state_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ContextOpenGL3 : public Context {
public:
    explicit ContextOpenGL3(const GraphicsWindow &);

    ~ContextOpenGL3() override = default;

    void viewport(int width, int height) override;

    void makeCurrent() const override;

    std::unique_ptr<VertexArray> createVertexArray() override;

    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) override;

    std::unique_ptr<IndexBuffer> createIndexBuffer(BufferHint usageHint, int sizeInBytes) override;

    void clear(const ClearState &) override;

    void draw(const DrawState &, const SceneState &) override;

private:
    const GraphicsWindow &_window;

    ClearState _clearState;
    RenderStateOpenGL3 _renderState;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr