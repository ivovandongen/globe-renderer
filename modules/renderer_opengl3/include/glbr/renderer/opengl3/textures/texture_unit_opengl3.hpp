#pragma once

#include <glbr/renderer/textures/texture_unit.hpp>

#include "texture2d_opengl3.hpp"
#include "texture_sampler_opengl3.hpp"

namespace glbr {
namespace renderer {
namespace opengl3 {

class ContextOpenGL3;

class TextureUnitOpenGL3 : public TextureUnit {
public:
    explicit TextureUnitOpenGL3(uint8_t index);

    ~TextureUnitOpenGL3() override;

    const Texture2D& texture() const override;
    void texture(std::shared_ptr<Texture2D> ptr) override;

    const TextureSampler& sampler() const override;
    void sampler(std::shared_ptr<TextureSampler> ptr) override;

    void clean(ContextOpenGL3& context);

    explicit operator bool() const { return texture_ && sampler_; }

    uint8_t index() const { return index_; }

private:
    uint8_t index_;
    uint8_t dirtyFlags_;
    std::shared_ptr<Texture2DOpenGL3> texture_;
    std::shared_ptr<TextureSamplerOpenGL3> sampler_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr