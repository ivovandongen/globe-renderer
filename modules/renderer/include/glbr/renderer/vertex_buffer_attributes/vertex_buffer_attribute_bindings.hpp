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

    VertexBufferAttributeBindings(std::initializer_list<AttributesCollection::value_type> vals) : attributes_(vals) {}

    virtual ~VertexBufferAttributeBindings() = default;

    const_iterator begin() const { return attributes_.begin(); }
    const_iterator end() const { return attributes_.end(); }
    const VertexBufferAttribute& operator[](const std::string& key) const { return attributes_.at(key); }
    const VertexBufferAttribute& at(const std::string& key) const { return attributes_.at(key); }

    virtual AttributesCollection::mapped_type& operator[](const std::string& key) { return attributes_[key]; }

protected:
    AttributesCollection attributes_;
};

}  // namespace renderer
}  // namespace glbr