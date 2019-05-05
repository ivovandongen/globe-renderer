#pragma once

#include <string>

namespace glbr {
namespace renderer {

class VertexAttribute {
public:
    enum class Type { Float };

    VertexAttribute(Type type, unsigned int components, bool normalize, unsigned int stride, unsigned int offset)
        : _components(components), _type(type), _normalize(normalize), _stride(stride), _offset(offset) {}

    virtual ~VertexAttribute() = default;

    Type type() { return _type; };
    unsigned int components() { return _components; }
    bool normalize() { return _normalize; }
    unsigned int stride() { return _stride; }
    unsigned int offset() { return _offset; }

private:
    Type _type;
    unsigned int _components;
    bool _normalize;
    unsigned int _stride;
    unsigned int _offset;
};

}  // namespace renderer
}  // namespace glbr