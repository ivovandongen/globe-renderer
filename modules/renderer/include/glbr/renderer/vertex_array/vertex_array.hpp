#pragma once

#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/vertex_buffer_attributes/vertex_buffer_attribute.hpp>

#include <memory>

namespace glbr {
namespace renderer {

class VertexArray {
public:
    virtual ~VertexArray() = default;

    virtual IndexBuffer *indexBuffer() = 0;

    virtual void indexBuffer(std::shared_ptr<IndexBuffer>) = 0;

    virtual void add(const std::string &key, VertexBufferAttribute) = 0;

    virtual void bind() = 0;

    virtual void unbind() = 0;

protected:
    VertexArray() = default;
};

}  // namespace renderer
}  // namespace glbr