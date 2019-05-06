#pragma once

#include "vertex_attribute.hpp"

#include <initializer_list>
#include <string>
#include <unordered_map>

namespace glbr {
namespace renderer {

class VertexAttributeBindings {
protected:
    using AttributesCollection = std::unordered_map<std::string, VertexAttribute>;

public:
    using const_iterator = AttributesCollection::const_iterator;

    VertexAttributeBindings() = default;

    VertexAttributeBindings(std::initializer_list<AttributesCollection::value_type> vals) : _attributes(vals) {}

    virtual ~VertexAttributeBindings() = default;

    const_iterator begin() const { return _attributes.begin(); }
    const_iterator end() const { return _attributes.end(); }
    const VertexAttribute& operator[](const std::string& key) const { return _attributes.at(key); }
    const VertexAttribute& at(const std::string& key) const { return _attributes.at(key); }

    virtual AttributesCollection::mapped_type& operator[](const std::string& key) { return _attributes[key]; }

protected:
    AttributesCollection _attributes;
};

}  // namespace renderer
}  // namespace glbr