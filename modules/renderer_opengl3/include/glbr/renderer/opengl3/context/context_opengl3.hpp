#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/buffers/vertex_buffer.hpp>
#include <glbr/renderer/context.hpp>
#include <glbr/renderer/graphics_window.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

#include <glbr/renderer/opengl3/context/binding_ops.hpp>
#include <glbr/renderer/opengl3/context/binding_state.hpp>
#include <glbr/renderer/opengl3/context/clear_state_opengl3.hpp>
#include <glbr/renderer/opengl3/context/render_state_opengl3.hpp>
#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_units_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ContextOpenGL3 : public Context {
public:
    explicit ContextOpenGL3(const GraphicsWindow &);

    ~ContextOpenGL3() override = default;

    void viewport(int width, int height) override;

    void makeCurrent() const override;

    Device &device() override;

    const Device &device() const override;

    std::unique_ptr<VertexArray> createVertexArray() const override;

    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) const override;

    std::unique_ptr<IndexBuffer> createIndexBuffer(IndexBufferType type, BufferHint usageHint,
                                                   uint32_t count) const override;

    void clear(const ClearState &) override;

    void draw(core::geometry::PrimitiveType, const DrawState &, const SceneState &, uint32_t offset) override;

    TextureUnits &textureUnits() override { return _textureUnits; };

private:
    const GraphicsWindow &_window;

    // Clear state
    ClearStateOpenGL3 _clearState;

    // Per context state
    TextureUnitsOpenGL3 _textureUnits;

    // Draw state
    RenderStateOpenGL3 _renderState;
    BindingState<PipelineOpenGL3> _pipeline;
    BindingState<VertexArrayOpenGL3> _vertexArray;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr