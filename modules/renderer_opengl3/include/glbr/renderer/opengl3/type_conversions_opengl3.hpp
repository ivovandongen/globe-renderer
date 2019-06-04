#pragma once

#include <glbr/renderer/render_state.hpp>
#include <glbr/renderer/textures/texture_format.hpp>

#include <glad/glad.h>
#include <glbr/renderer/textures/texture_magnification_filter.hpp>
#include <glbr/renderer/textures/texture_minification_filter.hpp>
#include <glbr/renderer/textures/texture_target.hpp>
#include <glbr/renderer/textures/texture_wrap.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

inline GLenum toPolygonMode(RasterizationMode mode) {
    switch (mode) {
        case RasterizationMode::Point:
            return GL_POINT;
        case RasterizationMode::Line:
            return GL_LINE;
        case RasterizationMode::Fill:
            return GL_FILL;
    }
}

inline GLint toInternalFormat(TextureFormat format) {
    switch (format) {
        case TextureFormat::RGB8:
            return GL_RGB8;
        case TextureFormat::RGB16:
            return GL_RGB16;
        case TextureFormat::RGBA8:
            return GL_RGBA8;
        case TextureFormat::RGB10A2:
            return GL_RGB10_A2;
        case TextureFormat::RGBA16:
            return GL_RGBA16;
        case TextureFormat::Depth16:
            return GL_DEPTH_COMPONENT16;
        case TextureFormat::Depth24:
            return GL_DEPTH_COMPONENT24;
        case TextureFormat::R8:
            return GL_R8;
        case TextureFormat::R16:
            return GL_R16;
        case TextureFormat::RG8:
            return GL_RG8;
        case TextureFormat::RG16:
            return GL_RG16;
        case TextureFormat::R16f:
            return GL_R16F;
        case TextureFormat::R32f:
            return GL_R32F;
        case TextureFormat::RG16f:
            return GL_RG16F;
        case TextureFormat::RG32f:
            return GL_RG32F;
        case TextureFormat::R8i:
            return GL_R8I;
        case TextureFormat::R8ui:
            return GL_R8UI;
        case TextureFormat::R16i:
            return GL_R16I;
        case TextureFormat::R16ui:
            return GL_R16UI;
        case TextureFormat::R32i:
            return GL_R32I;
        case TextureFormat::R32ui:
            return GL_R32UI;
        case TextureFormat::RG8i:
            return GL_RG8I;
        case TextureFormat::RG8ui:
            return GL_RG8UI;
        case TextureFormat::RG16i:
            return GL_RG16I;
        case TextureFormat::RG16ui:
            return GL_RG16UI;
        case TextureFormat::RG32i:
            return GL_RG32I;
        case TextureFormat::RG32ui:
            return GL_RG32UI;
        case TextureFormat::RGBA32f:
            return GL_RGBA32F;
        case TextureFormat::RGB32f:
            return GL_RGB32F;
        case TextureFormat::RGBA16f:
            return GL_RGBA16F;
        case TextureFormat::RGB16f:
            return GL_RGB16F;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH24_STENCIL8;
        case TextureFormat::R11fG11fB10f:
            return GL_R11F_G11F_B10F;
        case TextureFormat::RGB9E5:
            return GL_RGB9_E5;
        case TextureFormat::SRGB8:
            return GL_SRGB8;
        case TextureFormat::SRGB8A8:
            return GL_SRGB8_ALPHA8;
        case TextureFormat::Depth32f:
            return GL_DEPTH_COMPONENT32F;
        case TextureFormat::Depth32fStencil8:
            return GL_DEPTH32F_STENCIL8;
        case TextureFormat::RGBA32ui:
            return GL_RGBA32UI;
        case TextureFormat::RGB32ui:
            return GL_RGB32UI;
        case TextureFormat::RGBA16ui:
            return GL_RGBA16UI;
        case TextureFormat::RGB16ui:
            return GL_RGB16UI;
        case TextureFormat::RGBA8ui:
            return GL_RGBA8UI;
        case TextureFormat::RGB8ui:
            return GL_RGB8UI;
        case TextureFormat::RGBA32i:
            return GL_RGBA32I;
        case TextureFormat::RGB32i:
            return GL_RGB32I;
        case TextureFormat::RGBA16i:
            return GL_RGBA16I;
        case TextureFormat::RGB16i:
            return GL_RGB16I;
        case TextureFormat::RGBA8i:
            return GL_RGBA8I;
        case TextureFormat::RGB8i:
            return GL_RGB8I;
    }
}

inline GLenum toPixelFormat(TextureFormat textureFormat) {
    switch (textureFormat) {
        case TextureFormat::RGB8:
        case TextureFormat::RGB16:
            return GL_RGB;
        case TextureFormat::RGBA8:
        case TextureFormat::RGB10A2:
        case TextureFormat::RGBA16:
            return GL_RGBA;
        case TextureFormat::Depth16:
        case TextureFormat::Depth24:
            return GL_DEPTH_COMPONENT;
        case TextureFormat::R8:
        case TextureFormat::R16:
            return GL_R;
        case TextureFormat::RG8:
        case TextureFormat::RG16:
            return GL_RG;
        case TextureFormat::R16f:
        case TextureFormat::R32f:
            return GL_R;
        case TextureFormat::RG16f:
        case TextureFormat::RG32f:
            return GL_RG;
        case TextureFormat::R8i:
        case TextureFormat::R8ui:
        case TextureFormat::R16i:
        case TextureFormat::R16ui:
        case TextureFormat::R32i:
        case TextureFormat::R32ui:
            return GL_RED_INTEGER;
        case TextureFormat::RG8i:
        case TextureFormat::RG8ui:
        case TextureFormat::RG16i:
        case TextureFormat::RG16ui:
        case TextureFormat::RG32i:
        case TextureFormat::RG32ui:
            return GL_RG_INTEGER;
        case TextureFormat::RGBA32f:
            return GL_RGBA;
        case TextureFormat::RGB32f:
            return GL_RGB;
        case TextureFormat::RGBA16f:
            return GL_RGBA;
        case TextureFormat::RGB16f:
            return GL_RGB;
        case TextureFormat::Depth24Stencil8:
            return GL_DEPTH_STENCIL;
        case TextureFormat::R11fG11fB10f:
        case TextureFormat::RGB9E5:
            return GL_RGB;
        case TextureFormat::SRGB8:
            return GL_RGB_INTEGER;
        case TextureFormat::SRGB8A8:
            return GL_RGBA_INTEGER;
        case TextureFormat::Depth32f:
            return GL_DEPTH_COMPONENT;
        case TextureFormat::Depth32fStencil8:
            return GL_DEPTH_STENCIL;
        case TextureFormat::RGBA32ui:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB32ui:
            return GL_RGB_INTEGER;
        case TextureFormat::RGBA16ui:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB16ui:
            return GL_RGB_INTEGER;
        case TextureFormat::RGBA8ui:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB8ui:
            return GL_RGB_INTEGER;
        case TextureFormat::RGBA32i:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB32i:
            return GL_RGB_INTEGER;
        case TextureFormat::RGBA16i:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB16i:
            return GL_RGB_INTEGER;
        case TextureFormat::RGBA8i:
            return GL_RGBA_INTEGER;
        case TextureFormat::RGB8i:
            return GL_RGB_INTEGER;
    }
}

inline GLenum toTextureTarget(TextureTarget target) {
    switch (target) {
        case TextureTarget::Texture2D:
            return GL_TEXTURE_2D;
    }
}
inline GLenum toMinFilter(TextureMinificationFilter filter) {
    switch (filter) {
        case TextureMinificationFilter::NEAREST:
            return GL_NEAREST;
        case TextureMinificationFilter::LINEAR:
            return GL_LINEAR;
        case TextureMinificationFilter::NEAREST_MIPMAP_NEAREST:
            return GL_NEAREST_MIPMAP_NEAREST;
        case TextureMinificationFilter::LINEAR_MIPMAP_NEAREST:
            return GL_LINEAR_MIPMAP_NEAREST;
        case TextureMinificationFilter::NEAREST_MIPMAP_LINEAR:
            return GL_NEAREST_MIPMAP_LINEAR;
        case TextureMinificationFilter::LINEAR_MIPMAP_LINEAR:
            return GL_LINEAR_MIPMAP_LINEAR;
    }
}

inline GLenum toMagFilter(TextureMagnificationFilter filter) {
    switch (filter) {
        case TextureMagnificationFilter::NEAREST:
            return GL_NEAREST;
        case TextureMagnificationFilter::LINEAR:
            return GL_LINEAR;
    }
}

inline GLenum toWrap(TextureWrap wrap) {
    switch (wrap) {
        case TextureWrap::CLAMP:
            return GL_CLAMP_TO_EDGE;
        case TextureWrap::REPEAT:
            return GL_REPEAT;
        case TextureWrap::MIRRORED_REPEAT:
            return GL_MIRRORED_REPEAT;
    }
}

inline GLenum toWindingOrder(core::geometry::WindingOrder order) {
    using namespace core::geometry;

    switch (order) {
        case WindingOrder::CLOCK_WISE:
            return GL_CW;
        case WindingOrder::COUNTER_CLOCK_WISE:
            return GL_CCW;
    }
}

inline GLenum toCullFace(CullFace face) {
    switch (face) {
        case CullFace::FRONT:
            return GL_FRONT;
        case CullFace::BACK:
            return GL_BACK;
        case CullFace::FRONT_AND_BACK:
            return GL_FRONT_AND_BACK;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr