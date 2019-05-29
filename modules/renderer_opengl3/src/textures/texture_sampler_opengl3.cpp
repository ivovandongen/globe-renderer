#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

TextureSamplerOpenGL3::TextureSamplerOpenGL3(TextureMinificationFilter min, TextureMagnificationFilter mag,
                                             TextureWrap s, TextureWrap t) {
    GL_VERIFY(glGenSamplers(1, &_id));

    GL_VERIFY(glSamplerParameteri(_id, GL_TEXTURE_MIN_FILTER, toMinFilter(min)));
    GL_VERIFY(glSamplerParameteri(_id, GL_TEXTURE_MAG_FILTER, toMagFilter(mag)));
    GL_VERIFY(glSamplerParameteri(_id, GL_TEXTURE_WRAP_S, toWrap(s)));
    GL_VERIFY(glSamplerParameteri(_id, GL_TEXTURE_WRAP_T, toWrap(t)));
}

TextureSamplerOpenGL3::~TextureSamplerOpenGL3() {
    GL_VERIFY(glDeleteSamplers(1, &_id));
}

void TextureSamplerOpenGL3::bind(int loc) const {
    GL_VERIFY(glBindSampler(loc, _id));
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr