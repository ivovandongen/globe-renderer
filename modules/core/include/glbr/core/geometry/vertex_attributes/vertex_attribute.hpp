#include <utility>

#pragma once

#include "vertex_attribute_type.hpp"

#include <string>

namespace glbr {
namespace core {
namespace geometry {

class VertexAttribute {
public:
    VertexAttribute(std::string name, VertexAttributeType type, unsigned int components = 1, unsigned int offset = 0)
        : _name(std::move(name)), _type(type), _components(components), _offset(offset){};

    inline const std::string& name() const { return _name; };

    inline unsigned int components() const { return _components; };

    inline VertexAttributeType type() const { return _type; };

    inline unsigned int size() const { return sizeOf(_type) * components(); };

    inline unsigned int offset() const { return _offset; };

private:
    std::string _name;
    VertexAttributeType _type;
    unsigned int _components;
    unsigned int _offset;
};

}  // namespace geometry
}  // namespace core
}  // namespace glbr