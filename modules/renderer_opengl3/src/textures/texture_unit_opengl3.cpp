#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

namespace {
enum DIRTY { NONE = 0, TEXTURE = 1, SAMPLER = 2 };
}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

TextureUnitOpenGL3::TextureUnitOpenGL3(uint8_t index) : _index(index), _dirtyFlags(DIRTY::NONE) {}

TextureUnitOpenGL3::~TextureUnitOpenGL3() = default;

const Texture2D& TextureUnitOpenGL3::texture() const {
    return *_texture;
}

void TextureUnitOpenGL3::texture(std::shared_ptr<Texture2D> texture) {
    if (!_texture || *_texture != *std::dynamic_pointer_cast<Texture2DOpenGL3>(texture)) {
        _dirtyFlags |= DIRTY::TEXTURE;
    }
    _texture = std::move(std::dynamic_pointer_cast<Texture2DOpenGL3>(texture));
}

const TextureSampler& TextureUnitOpenGL3::sampler() const {
    return *_sampler;
}

void TextureUnitOpenGL3::sampler(std::shared_ptr<TextureSampler> sampler) {
    if (!_sampler || *_sampler != *std::dynamic_pointer_cast<TextureSamplerOpenGL3>(sampler)) {
        _dirtyFlags |= DIRTY::SAMPLER;
    }
    _sampler = std::move(std::dynamic_pointer_cast<TextureSamplerOpenGL3>(sampler));
}

void TextureUnitOpenGL3::clean(ContextOpenGL3& context) {
    if (_dirtyFlags > 0) {
        context.activeTextureUnit(*this);

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