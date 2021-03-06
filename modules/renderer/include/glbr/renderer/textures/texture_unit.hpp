#pragma once

#include "texture2d.hpp"
#include "texture_sampler.hpp"

#include <memory>

namespace glbr {
namespace renderer {

class TextureUnit {
public:
    virtual ~TextureUnit() = default;

    void operator()(std::shared_ptr<Texture2D> t, std::shared_ptr<TextureSampler> s) {
        texture(std::move(t));
        sampler(std::move(s));
    }

    virtual const Texture2D& texture() const = 0;
    virtual void texture(std::shared_ptr<Texture2D>) = 0;

    virtual const TextureSampler& sampler() const = 0;
    virtual void sampler(std::shared_ptr<TextureSampler>) = 0;
};

}  // namespace renderer
}  // namespace glbr