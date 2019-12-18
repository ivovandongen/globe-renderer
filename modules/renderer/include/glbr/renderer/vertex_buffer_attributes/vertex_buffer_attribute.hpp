#pragma once

#include <glbr/renderer/buffers/vertex_buffer.hpp>

#include <memory>
#include <string>

namespace glbr {
namespace renderer {

class VertexBufferAttribute {
public:
    enum class Type { Float, UnsignedByte };

    VertexBufferAttribute() = default;

    VertexBufferAttribute(std::shared_ptr<VertexBuffer> buffer,
                          Type type,
                          unsigned int components,
                          bool normalize,
                          unsigned int stride,
                          unsigned int offset)
        : buffer_(std::move(buffer)),
          type_(type),
          components_(components),
          normalize_(normalize),
          stride_(stride),
          offset_(offset) {}

    ~VertexBufferAttribute() = default;

    const VertexBuffer& buffer() { return *buffer_; }
    Type type() const { return type_; };
    unsigned int components() const { return components_; }
    bool normalize() const { return normalize_; }
    unsigned int stride() const { return stride_; }
    unsigned int offset() const { return offset_; }

private:
    std::shared_ptr<VertexBuffer> buffer_;
    Type type_;
    unsigned int components_{};
    bool normalize_{};
    unsigned int stride_{};
    unsigned int offset_{};
};

}  // namespace renderer
}  // namespace glbr