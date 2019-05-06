#pragma once

#include <glbr/renderer/shaders/shader_vertex_attribute.hpp>
#include <glbr/renderer/vertex_attributes/vertex_attribute.hpp>
#include <glbr/renderer/vertex_attributes/vertex_attribute_bindings.hpp>

#include <string>
#include <unordered_map>
#include <vector>

namespace glbr {
namespace renderer {
namespace opengl3 {

class VertexAttributeBindingsOpenGL3 : public VertexAttributeBindings {
public:
    VertexAttributeBindingsOpenGL3() = default;

    VertexAttributeBindingsOpenGL3(
        std::initializer_list<VertexAttributeBindings::AttributesCollection::value_type> vals)
        : VertexAttributeBindings(vals), _dirty{true} {}

    VertexAttribute& operator[](const std::string& key) override {
        _dirty = true;
        return VertexAttributeBindings::operator[](key);
    }

    bool dirty() { return _dirty; }

    void clean(const std::vector<ShaderVertexAttribute>&);

private:
    bool _dirty{false};
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr