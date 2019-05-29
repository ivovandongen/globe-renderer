#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

namespace {
enum DIRTY { NONE = 0, TEXTURE = 1, SAMPLER = 2 };
}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

TextureUnitOpenGL3::TextureUnitOpenGL3(int index) : _index(index), _dirtyFlags(DIRTY::NONE) {}

TextureUnitOpenGL3::~TextureUnitOpenGL3() = default;

const Texture2D& TextureUnitOpenGL3::texture() const {
    return *_texture;
}

void TextureUnitOpenGL3::texture(std::shared_ptr<Texture2D> texture) {
    // TODO: check if the texture is actually different
    _texture = std::move(std::dynamic_pointer_cast<Texture2DOpenGL3>(texture));
    _dirtyFlags |= DIRTY::TEXTURE;
}

const TextureSampler& TextureUnitOpenGL3::sampler() const {
    return *_sampler;
}

void TextureUnitOpenGL3::sampler(std::shared_ptr<TextureSampler> sampler) {
    // TODO: check if the sampler is actually different
    _sampler = std::move(std::dynamic_pointer_cast<TextureSamplerOpenGL3>(sampler));
    _dirtyFlags |= DIRTY::SAMPLER;
}

void TextureUnitOpenGL3::clean() {
    if (_dirtyFlags > 0) {
        logging::debug("Cleaning texture unit {}", _index);
        GL_VERIFY(glActiveTexture(GL_TEXTURE0 + _index));

        if (_dirtyFlags & DIRTY::TEXTURE && _texture) {
            _texture->bind();
        }

        if (_dirtyFlags & DIRTY::SAMPLER && _sampler) {
            _sampler->bind(_index);
        }

        _dirtyFlags = DIRTY::NONE;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr