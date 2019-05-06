#pragma once

#include <string>

namespace glbr {
namespace renderer {

class VertexAttribute {
public:
    enum class Type { Float };

    VertexAttribute() = default;

    VertexAttribute(Type type, unsigned int components, bool normalize, unsigned int stride, unsigned int offset)
        : _components(components), _type(type), _normalize(normalize), _stride(stride), _offset(offset) {}

    ~VertexAttribute() = default;

    Type type() const { return _type; };
    unsigned int components() const { return _components; }
    bool normalize() const { return _normalize; }
    unsigned int stride() const { return _stride; }
    unsigned int offset() const { return _offset; }

private:
    Type _type;
    unsigned int _components;
    bool _normalize;
    unsigned int _stride;
    unsigned int _offset;
};

}  // namespace renderer
}  // namespace glbr