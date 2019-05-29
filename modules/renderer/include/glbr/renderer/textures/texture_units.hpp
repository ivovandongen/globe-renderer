#pragma once

#include "texture2d.hpp"
#include "texture_sampler.hpp"
#include "texture_unit.hpp"

#include <memory>

namespace glbr {
namespace renderer {

class TextureUnits {
public:
    virtual ~TextureUnits() = default;

    virtual TextureUnit& operator[](int i) = 0;
};

}  // namespace renderer
}  // namespace glbr