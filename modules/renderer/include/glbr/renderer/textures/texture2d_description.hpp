#pragma once

#include "texture_format.hpp"

namespace glbr {
namespace renderer {

class Texture2DDescription {
public:
    Texture2DDescription(int width, int height, TextureFormat format, bool generateMipmaps)
        : width_(width), height_(height), format_(format), generateMipmaps_(generateMipmaps) {}

    int width() const { return width_; }

    int height() const { return height_; }

    TextureFormat format() const { return format_; }

    bool generateMipmaps() const { return generateMipmaps_; }

private:
    int width_;
    int height_;
    TextureFormat format_;
    bool generateMipmaps_;
};

}  // namespace renderer
}  // namespace glbr