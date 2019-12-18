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

    void clean(const Context &, const DrawState &, const SceneState &);

    const VertexAttributeBindings &vertexAttributeBindings() const override { return vertexAttributeBindings_; }

    const Uniforms &uniforms() const override { return uniforms_; }

    Uniforms &uniforms() override { return uniforms_; }

    GLuint id() const { return id_; }

    bool operator==(const PipelineOpenGL3 &other) { return id_ == other.id_; }
    bool operator!=(const PipelineOpenGL3 &other) { return !(*this == other); }

private:
    void loadVertexAttributes();
    void loadUniforms();

private:
    GLuint id_;
    VertexAttributeBindings vertexAttributeBindings_;
    Uniforms uniforms_;
    std::vector<DrawAutoUniform> drawAutoUniforms_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr