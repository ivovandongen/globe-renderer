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
        : name_(std::move(name)), type_(type), components_(components), offset_(offset){};

    inline const std::string& name() const { return name_; };

    inline unsigned int components() const { return components_; };

    inline VertexAttributeType type() const { return type_; };

    inline unsigned int size() const { return sizeOf(type_) * components(); };

    inline unsigned int offset() const { return offset_; };

private:
    std::string name_;
    VertexAttributeType type_;
    unsigned int components_;
    unsigned int offset_;
};

}  // namespace geometry
}  // namespace core
}  // namespace glbr