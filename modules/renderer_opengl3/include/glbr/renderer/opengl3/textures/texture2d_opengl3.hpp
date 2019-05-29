#pragma once

#include <glbr/renderer/textures/texture2d.hpp>
#include <glbr/renderer/textures/texture2d_description.hpp>
#include <glbr/renderer/textures/texture_target.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

class Texture2DOpenGL3 : public Texture2D {
public:
    Texture2DOpenGL3(Texture2DDescription, TextureTarget);

    ~Texture2DOpenGL3() override;

    void bind() const override;

    void upload(const void* data) const override;

private:
    GLuint _id{};
    GLenum _target;
    Texture2DDescription _description;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr