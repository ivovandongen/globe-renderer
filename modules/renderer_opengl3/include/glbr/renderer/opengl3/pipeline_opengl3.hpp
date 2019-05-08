#pragma once

#include <glbr/renderer/pipeline.hpp>

#include <glad/glad.h>

#include <string>
#include <vector>

namespace glbr {
namespace renderer {
namespace opengl3 {

class PipelineOpenGL3 : public Pipeline {
public:
    PipelineOpenGL3(const std::string &vert, const std::string &frag);

    // TODO: specify bindings up front PipelineOpenGL3(const std::string &vert, const std::string &frag);

    ~PipelineOpenGL3() override;

    void bind() override;

    const VertexAttributeBindings &vertexAttributeBindings() const override { return _vertexAttributeBindings; }

    const Uniforms &uniforms() const override { return _uniforms; }

    Uniforms &uniforms() override { return _uniforms; }

private:
    void loadVertexAttributes();
    void loadUniforms();

private:
    GLuint _id;
    VertexAttributeBindings _vertexAttributeBindings;
    Uniforms _uniforms;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr