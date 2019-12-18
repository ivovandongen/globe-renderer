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
    assert([]() {
        GLint boundTexture;
        GL_VERIFY(glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture));
        return boundTexture;
    }() == _id);

    GL_VERIFY(glTexImage2D(_target,
                           0,
                           toPixelFormat(_description.format()),
                           _description.width(),
                           _description.height(),
                           0,
                           toPixelFormat(_description.format()),
                           GL_UNSIGNED_BYTE,
                           data));

    if (_description.generateMipmaps()) {
        GL_VERIFY(glGenerateMipmap(_target));
    }
}

Texture2DOpenGL3WithImageData::Texture2DOpenGL3WithImageData(const core::Image& image,
                                                             TextureTarget target,
                                                             bool generateMipMaps)
    : Texture2DOpenGL3({image.width(), image.height(), TextureFormatFromImage(image), generateMipMaps}, target),
      image_(image) {}

void Texture2DOpenGL3WithImageData::bind() const {
    Texture2DOpenGL3::bind();
    if (!uploaded_) {
        Texture2DOpenGL3::upload(image_.data());
        uploaded_ = true;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr