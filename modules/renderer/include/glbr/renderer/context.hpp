#pragma once

#include <glbr/renderer/buffers/buffer_hint.hpp>
#include <glbr/renderer/buffers/vertex_buffer.hpp>
#include <glbr/renderer/clear_state.hpp>
#include <glbr/renderer/draw_state.hpp>
#include <glbr/renderer/scene/scene_state.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

namespace glbr {
namespace renderer {

class Context {
public:
    virtual ~Context() = default;

    virtual void resize(int width, int height) = 0;

    virtual void makeCurrent() const = 0;

    virtual std::unique_ptr<VertexArray> createVertexArray() = 0;

    virtual std::unique_ptr<IndexBuffer> createIndexBuffer(BufferHint usageHint, int sizeInBytes) = 0;

    virtual std::unique_ptr<VertexBuffer> createVertexBuffer(BufferHint usageHint, int sizeInBytes) = 0;

    virtual void clear(const ClearState &) = 0;

    virtual void draw(/* TODO: PrimitiveType */ const DrawState &, const SceneState &) = 0;
};

}  // namespace renderer
}  // namespace glbr