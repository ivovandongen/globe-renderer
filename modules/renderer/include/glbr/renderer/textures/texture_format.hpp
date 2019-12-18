#pragma once

#include <glbr/core/image.hpp>

namespace glbr {
namespace renderer {

enum class TextureFormat {
    RGB8,
    RGB16,
    RGBA8,
    RGB10A2,
    RGBA16,
    Depth16,
    Depth24,
    R8,
    R16,
    RG8,
    RG16,
    R16f,
    R32f,
    RG16f,
    RG32f,
    R8i,
    R8ui,
    R16i,
    R16ui,
    R32i,
    R32ui,
    RG8i,
    RG8ui,
    RG16i,
    RG16ui,
    RG32i,
    RG32ui,
    RGBA32f,
    RGB32f,
    RGBA16f,
    RGB16f,
    Depth24Stencil8,
    R11fG11fB10f,
    RGB9E5,
    SRGB8,
    SRGB8A8,
    Depth32f,
    Depth32fStencil8,
    RGBA32ui,
    RGB32ui,
    RGBA16ui,
    RGB16ui,
    RGBA8ui,
    RGB8ui,
    RGBA32i,
    RGB32i,
    RGBA16i,
    RGB16i,
    RGBA8i,
    RGB8i
};

inline TextureFormat TextureFormatFromImage(const core::Image& image) {
    switch (image.channels()) {
        case 1:
            return TextureFormat::R8;
        case 2:
            return TextureFormat::RG8;
        case 4:
            return TextureFormat::RGBA8;
        case 3:
        default:
            return TextureFormat::RGB8;
    }
}

}  // namespace renderer
}  // namespace glbr