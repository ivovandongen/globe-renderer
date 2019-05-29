#pragma once

#include "texture_format.hpp"

namespace glbr {
namespace renderer {

class Texture2DDescription {
public:
    Texture2DDescription(int width, int height, TextureFormat format, bool generateMipmaps)
        : _width(width), _height(height), _format(format), _generateMipmaps(generateMipmaps) {}

    int width() const { return _width; }

    int height() const { return _height; }

    TextureFormat format() const { return _format; }

    bool generateMipmaps() const { return _generateMipmaps; }

private:
    int _width;
    int _height;
    TextureFormat _format;
    bool _generateMipmaps;
};

}  // namespace renderer
}  // namespace glbr