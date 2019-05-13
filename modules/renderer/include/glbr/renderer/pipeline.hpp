#pragma once

#include <glbr/renderer/shaders/shader_vertex_attribute.hpp>
#include <glbr/renderer/shaders/uniforms.hpp>
#include <glbr/renderer/vertex_buffer_attributes/vertex_buffer_attribute_bindings.hpp>

#include <vector>

namespace glbr {
namespace renderer {

class Pipeline {
public:
    using VertexAttributeBindings = std::vector<ShaderVertexAttribute>;

public:
    virtual ~Pipeline() = default;

    virtual void bind() = 0;

    virtual const VertexAttributeBindings &vertexAttributeBindings() const = 0;

    virtual const Uniforms &uniforms() const = 0;

    virtual Uniforms &uniforms() = 0;
};

}  // namespace renderer
}  // namespace glbr