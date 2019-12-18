#pragma once

#include <glbr/renderer/shaders/shader_vertex_attribute.hpp>
#include <glbr/renderer/vertex_buffer_attributes/vertex_buffer_attribute.hpp>
#include <glbr/renderer/vertex_buffer_attributes/vertex_buffer_attribute_bindings.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace glbr {
namespace renderer {
namespace opengl3 {

class VertexBufferAttributeBindingsOpenGL3 : public VertexBufferAttributeBindings {
public:
    VertexBufferAttributeBindingsOpenGL3() = default;

    VertexBufferAttributeBindingsOpenGL3(
        std::initializer_list<VertexBufferAttributeBindings::AttributesCollection::value_type> vals)
        : VertexBufferAttributeBindings(vals), dirty_{true} {}

    VertexBufferAttribute& operator[](const std::string& key) override {
        dirty_ = true;
        return VertexBufferAttributeBindings::operator[](key);
    }

    bool dirty() { return dirty_; }

    void clean(const std::vector<ShaderVertexAttribute>&);

private:
    bool dirty_{false};
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr