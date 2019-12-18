#include <glbr/renderer/opengl3/textures/texture2d_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

Texture2DOpenGL3::Texture2DOpenGL3(Texture2DDescription description, TextureTarget target)
    : target_(toTextureTarget(target)), description_(description) {
    GL_VERIFY(glGenTextures(1, &id_));
}

Texture2DOpenGL3::~Texture2DOpenGL3() {
    GL_VERIFY(glDeleteTextures(1, &id_));
}

void Texture2DOpenGL3::bind() const {
    GL_VERIFY(glBindTexture(target_, id_));
}

void Texture2DOpenGL3::upload(const void* data) const {
    assert([]() {
        GLint boundTexture;
        GL_VERIFY(glGetIntegerv(GL_TEXTURE_BINDING_2D, &boundTexture));
        return boundTexture;
    }() == id_);

    GL_VERIFY(glTexImage2D(target_,
                           0,
                           toPixelFormat(description_.format()),
                           description_.width(),
                           description_.height(),
                           0,
                           toPixelFormat(description_.format()),
                           GL_UNSIGNED_BYTE,
                           data));

    if (description_.generateMipmaps()) {
        GL_VERIFY(glGenerateMipmap(target_));
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