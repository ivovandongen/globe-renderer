#pragma once

#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/shaders/auto_uniforms/draw_auto_uniform.hpp>

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

    void bind() const override;

    void clean(const Context&, const DrawState&, const SceneState&);

    const VertexAttributeBindings &vertexAttributeBindings() const override { return _vertexAttributeBindings; }

    const Uniforms &uniforms() const override { return _uniforms; }

    Uniforms &uniforms() override { return _uniforms; }

    GLuint id() const { return _id; }

    bool operator==(const PipelineOpenGL3 &other) { return _id == other._id; }
    bool operator!=(const PipelineOpenGL3 &other) { return !(*this == other); }

private:
    void loadVertexAttributes();
    void loadUniforms();

private:
    GLuint _id;
    VertexAttributeBindings _vertexAttributeBindings;
    Uniforms _uniforms;
    std::vector<DrawAutoUniform> _drawAutoUniforms;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr