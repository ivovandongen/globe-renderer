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

    const std::vector<ShaderVertexAttribute> &vertexAttributeBindings() const override {
        return _vertexAttributeBindings;
    }

    void setUniform(const std::string &name, bool value) const override;

    void setUniform(const std::string &name, unsigned int value) const override;

    void setUniform(const std::string &name, int value) const override;

    void setUniform(const std::string &name, float value) const override;

    void setUniform(const std::string &name, float x, float y) const override;

    void setUniform(const std::string &name, float x, float y, float z) const override;

    void setUniform(const std::string &name, float x, float y, float z, float w) const override;

    void setUniform(const std::string &name, glm::vec2 value) const override;

    void setUniform(const std::string &name, glm::vec3 value) const override;

    void setUniform(const std::string &name, glm::vec4 value) const override;

    void setUniform(const std::string &name, glm::mat4 value) const override;

private:
    void loadVertexAttributes();

private:
    GLuint _id;
    std::vector<ShaderVertexAttribute> _vertexAttributeBindings;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr