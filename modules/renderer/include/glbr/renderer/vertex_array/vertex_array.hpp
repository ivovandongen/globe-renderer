#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/vertex_attributes/vertex_attribute.hpp>

#include <memory>

namespace glbr {
namespace renderer {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual void bind() = 0;

    virtual IndexBuffer *indexBuffer() = 0;

    virtual void indexBuffer(std::unique_ptr<IndexBuffer>) = 0;

    virtual void add(VertexAttribute) = 0;

protected:
    VertexArray() = default;
};

}  // namespace renderer
}  // namespace glbr