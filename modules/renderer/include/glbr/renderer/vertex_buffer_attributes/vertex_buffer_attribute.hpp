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

    VertexBufferAttribute(std::shared_ptr<VertexBuffer> buffer, Type type, unsigned int components, bool normalize,
                          unsigned int stride, unsigned int offset)
        : _buffer(std::move(buffer)),
          _type(type),
          _components(components),
          _normalize(normalize),
          _stride(stride),
          _offset(offset) {}

    ~VertexBufferAttribute() = default;

    const VertexBuffer& buffer() { return *_buffer; }
    Type type() const { return _type; };
    unsigned int components() const { return _components; }
    bool normalize() const { return _normalize; }
    unsigned int stride() const { return _stride; }
    unsigned int offset() const { return _offset; }

private:
    std::shared_ptr<VertexBuffer> _buffer;
    Type _type;
    unsigned int _components{};
    bool _normalize{};
    unsigned int _stride{};
    unsigned int _offset{};
};

}  // namespace renderer
}  // namespace glbr