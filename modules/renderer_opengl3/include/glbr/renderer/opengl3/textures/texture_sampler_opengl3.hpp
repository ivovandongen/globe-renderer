#pragma once

#include <glbr/renderer/textures/texture_magnification_filter.hpp>
#include <glbr/renderer/textures/texture_minification_filter.hpp>
#include <glbr/renderer/textures/texture_sampler.hpp>
#include <glbr/renderer/textures/texture_wrap.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

class TextureSamplerOpenGL3 : public TextureSampler {
public:
    TextureSamplerOpenGL3(TextureMinificationFilter, TextureMagnificationFilter, TextureWrap s, TextureWrap t);

    ~TextureSamplerOpenGL3() override;

    void bind(int textureUnit) const override;

    bool operator==(const TextureSamplerOpenGL3 &other) const { return _id == other._id; }
    bool operator!=(const TextureSamplerOpenGL3 &other) const { return _id != other._id; }

private:
    GLuint _id{};
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr