#pragma once

#include <glbr/core/geometry/mesh.hpp>
#include <glbr/core/geometry/primitive_type.hpp>
#include <glbr/core/optional.hpp>
#include <glbr/renderer/buffers/buffer_hint.hpp>
#include <glbr/renderer/buffers/vertex_buffer.hpp>
#include <glbr/renderer/clear_state.hpp>
#include <glbr/renderer/device.hpp>
#include <glbr/renderer/draw_state.hpp>
#include <glbr/renderer/scene/scene_state.hpp>
#include <glbr/renderer/textures/texture_unit.hpp>
#include <glbr/renderer/textures/texture_units.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

namespace glbr {
namespace renderer {

class Context {
public:
    using ResizeFN = std::function<void(float, float)>;

    virtual ~Context() = default;

    std::unique_ptr<VertexArray> createVertexArray(const core::geometry::Mesh &) const;

    std::unique_ptr<IndexBuffer> createIndexBuffer(IndexBufferType type, BufferHint usageHint) const {
        return createIndexBuffer(type, usageHint, 0);
    }

    std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint) const {
        return createVertexBuffer(usageHint, 0);
    }

    void draw(core::geometry::PrimitiveType primitive, const DrawState &drawState, const SceneState &sceneState) {
        draw(primitive, drawState, sceneState, 0);
    };

    void setOnResizeListener(const ResizeFN &onResize) { _onResizeListener = onResize; };

    // Needs to be called from sub-classes
    virtual void viewport(int width, int height);

    virtual void makeCurrent() const = 0;

    virtual Device &device() = 0;

    virtual const Device &device() const = 0;

    virtual std::unique_ptr<VertexArray> createVertexArray() const = 0;

    virtual std::unique_ptr<IndexBuffer> createIndexBuffer(IndexBufferType type, BufferHint usageHint,
                                                           uint32_t count) const = 0;

    virtual std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) const = 0;

    virtual void clear(const ClearState &) = 0;

    virtual void draw(core::geometry::PrimitiveType primitive, const DrawState &, const SceneState &,
                      uint32_t offset) = 0;

    virtual TextureUnits &textureUnits() = 0;

protected:
    core::optional<ResizeFN> _onResizeListener;
};

}  // namespace renderer
}  // namespace glbr