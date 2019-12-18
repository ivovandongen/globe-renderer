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
#include <glbr/renderer/opengl3/textures/active_texture_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_units_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_array/vertex_array_opengl3.hpp>

#include <memory>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ContextOpenGL3 : public Context, public std::enable_shared_from_this<ContextOpenGL3> {
public:
    explicit ContextOpenGL3(const GraphicsWindow &);

    ~ContextOpenGL3() override = default;

    void viewport(int width, int height) override;

    void makeCurrent() const override;

    Device &device() override;

    const Device &device() const override;

    std::shared_ptr<VertexArray> createVertexArray() override;

    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) const override;

    std::unique_ptr<IndexBuffer> createIndexBuffer(IndexBufferType type,
                                                   BufferHint usageHint,
                                                   uint32_t count) const override;

    void clear(const ClearState &) override;

    void draw(core::geometry::PrimitiveType, const DrawState &, const SceneState &, uint32_t offset) override;

    TextureUnits &textureUnits() override { return textureUnits_; };

    void activeTextureUnit(const TextureUnitOpenGL3 &unit);

    void set(const std::shared_ptr<VertexArrayOpenGL3> &array) { vertexArray_ = array; }

private:
    const GraphicsWindow &window_;

    // Clear state
    ClearStateOpenGL3 clearState_;

    // Per context state
    BindingState<ActiveTextureUnitOpenGL3> activeTextureUnit_;
    TextureUnitsOpenGL3 textureUnits_;

    // Draw state
    RenderStateOpenGL3 renderState_;
    BindingState<PipelineOpenGL3> pipeline_;
    BindingState<VertexArrayOpenGL3> vertexArray_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr