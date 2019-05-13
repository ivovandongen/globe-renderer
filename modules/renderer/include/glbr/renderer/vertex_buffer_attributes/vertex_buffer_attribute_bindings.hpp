#pragma once

#include "vertex_buffer_attribute.hpp"

#include <initializer_list>
#include <string>
#include <unordered_map>

namespace glbr {
namespace renderer {

class VertexBufferAttributeBindings {
protected:
    using AttributesCollection = std::unordered_map<std::string, VertexBufferAttribute>;

public:
    using const_iterator = AttributesCollection::const_iterator;

    VertexBufferAttributeBindings() = default;

    VertexBufferAttributeBindings(std::initializer_list<AttributesCollection::value_type> vals) : _attributes(vals) {}

    virtual ~VertexBufferAttributeBindings() = default;

    const_iterator begin() const { return _attributes.begin(); }
    const_iterator end() const { return _attributes.end(); }
    const VertexBufferAttribute& operator[](const std::string& key) const { return _attributes.at(key); }
    const VertexBufferAttribute& at(const std::string& key) const { return _attributes.at(key); }

    virtual AttributesCollection::mapped_type& operator[](const std::string& key) { return _attributes[key]; }

protected:
    AttributesCollection _attributes;
};

}  // namespace renderer
}  // namespace glbr