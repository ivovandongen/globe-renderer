#pragma once

#include <renderer/buffers/buffer_hint.hpp>
#include <renderer/buffers/vertex_buffer.hpp>
#include <renderer/clear_state.hpp>
#include <renderer/draw_state.hpp>
#include <renderer/vertex_array/vertex_array.hpp>

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

    virtual void draw(const DrawState &) = 0;
};

}  // namespace renderer