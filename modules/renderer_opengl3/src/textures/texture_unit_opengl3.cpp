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

TextureUnitOpenGL3::TextureUnitOpenGL3(uint8_t index) : index_(index), dirtyFlags_(DIRTY::NONE) {}

TextureUnitOpenGL3::~TextureUnitOpenGL3() = default;

const Texture2D& TextureUnitOpenGL3::texture() const {
    return *texture_;
}

void TextureUnitOpenGL3::texture(std::shared_ptr<Texture2D> texture) {
    if (!texture_ || *texture_ != *std::dynamic_pointer_cast<Texture2DOpenGL3>(texture)) {
        dirtyFlags_ |= DIRTY::TEXTURE;
    }
    texture_ = std::move(std::dynamic_pointer_cast<Texture2DOpenGL3>(texture));
}

const TextureSampler& TextureUnitOpenGL3::sampler() const {
    return *sampler_;
}

void TextureUnitOpenGL3::sampler(std::shared_ptr<TextureSampler> sampler) {
    if (!sampler_ || *sampler_ != *std::dynamic_pointer_cast<TextureSamplerOpenGL3>(sampler)) {
        dirtyFlags_ |= DIRTY::SAMPLER;
    }
    sampler_ = std::move(std::dynamic_pointer_cast<TextureSamplerOpenGL3>(sampler));
}

void TextureUnitOpenGL3::clean(ContextOpenGL3& context) {
    if (dirtyFlags_ > 0) {
        context.activeTextureUnit(*this);

        if (dirtyFlags_ & DIRTY::TEXTURE && texture_) {
            texture_->bind();
        }

        if (dirtyFlags_ & DIRTY::SAMPLER && sampler_) {
            sampler_->bind(index_);
        }

        dirtyFlags_ = DIRTY::NONE;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr