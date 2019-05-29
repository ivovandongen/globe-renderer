#include <glbr/renderer/opengl3/textures/texture2d_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

Texture2DOpenGL3::Texture2DOpenGL3(Texture2DDescription description, TextureTarget target)
    : _target(toTextureTarget(target)), _description(description) {
    GL_VERIFY(glGenTextures(1, &_id));
}

Texture2DOpenGL3::~Texture2DOpenGL3() {
    GL_VERIFY(glDeleteTextures(1, &_id));
}

void Texture2DOpenGL3::bind() const {
    GL_VERIFY(glBindTexture(_target, _id));
}

void Texture2DOpenGL3::upload(const void* data) const {
    bind();

    GL_VERIFY(glTexImage2D(_target, 0, toPixelFormat(_description.format()), _description.width(),
                           _description.height(), 0, toPixelFormat(_description.format()), GL_UNSIGNED_BYTE, data));

    if (_description.generateMipmaps()) {
        GL_VERIFY(glGenerateMipmap(_target));
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr