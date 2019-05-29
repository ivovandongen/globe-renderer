#pragma once

namespace glbr {
namespace renderer {

class TextureSampler {
public:
    virtual ~TextureSampler() = default;

    virtual void bind(int textureUnit) const = 0;
};

}  // namespace renderer
}  // namespace glbr