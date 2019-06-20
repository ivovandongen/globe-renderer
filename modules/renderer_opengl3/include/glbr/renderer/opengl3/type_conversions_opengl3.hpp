#pragma once

#include <glbr/core/geometry/primitive_type.hpp>
#include <glbr/renderer/buffers/index_buffer.hpp>
#include <glbr/renderer/render_state.hpp>
#include <glbr/renderer/state/clear_buffers.hpp>
#include <glbr/renderer/textures/texture_format.hpp>
#include <glbr/renderer/textures/texture_magnification_filter.hpp>
#include <glbr/renderer/textures/texture_minification_filter.hpp>
#include <glbr/renderer/textures/texture_target.hpp>
#include <glbr/renderer/textures/texture_wrap.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

inline GLenum toPolygonMode(RasterizationMode mode) {
    switch (mode) {
        case RasterizationMode::POINT:
            return GL_POINT;
        case RasterizationMode::LINE:
            return GL_LINE;
        case RasterizationMode::FILL:
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

inline GLenum toPrimitiveType(core::geometry::PrimitiveType type) {
    using namespace core::geometry;

    switch (type) {
        case PrimitiveType::POINTS:
            return GL_POINTS;
        case PrimitiveType::LINES:
            return GL_LINES;
        case PrimitiveType::LINE_LOOP:
            return GL_LINE_LOOP;
        case PrimitiveType::LINE_STRIP:
            return GL_LINE_STRIP;
        case PrimitiveType::TRIANGLES:
            return GL_TRIANGLES;
        case PrimitiveType::TRIANGLE_STRIP:
            return GL_TRIANGLE_STRIP;
        case PrimitiveType::TRIANGLE_FAN:
            return GL_TRIANGLE_FAN;
        case PrimitiveType::LINES_ADJACENCY:
            return GL_LINES_ADJACENCY;
        case PrimitiveType::LINE_STRIP_ADJACENCY:
            return GL_LINE_STRIP_ADJACENCY;
        case PrimitiveType::TRIANGLES_ADJACENCY:
            return GL_TRIANGLES_ADJACENCY;
        case PrimitiveType::TRIANGLE_STRIP_ADJACENCY:
            return GL_TRIANGLE_STRIP_ADJACENCY;
    }
}

inline GLbitfield toClearBitfield(ClearBuffers buffers) {
    switch (buffers) {
        case ClearBuffers::COLOR:
            return GL_COLOR_BUFFER_BIT;
        case ClearBuffers::DEPTH:
            return GL_DEPTH_BUFFER_BIT;
        case ClearBuffers::STENCIL:
            return GL_STENCIL_BUFFER_BIT;
        case ClearBuffers::COLOR_AND_DEPTH:
            return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
        case ClearBuffers::ALL:
            return GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
    }
}

inline GLenum toBlendEquationMode(BlendEquation equation) {
    switch (equation) {
        case BlendEquation::ADD:
            return GL_FUNC_ADD;
        case BlendEquation::MINIMUM:
            return GL_MIN;
        case BlendEquation::MAXIMUM:
            return GL_MAX;
        case BlendEquation::SUBTRACT:
            return GL_FUNC_SUBTRACT;
        case BlendEquation::REVERSE_SUBTRACT:
            return GL_FUNC_REVERSE_SUBTRACT;
    }
}

inline GLenum toSourceBlendingFactor(SourceBlendingFactor factor) {
    switch (factor) {
        case SourceBlendingFactor::ZERO:
            return GL_ZERO;
        case SourceBlendingFactor::ONE:
            return GL_ONE;
        case SourceBlendingFactor::SOURCE_ALPHA:
            return GL_SRC_ALPHA;
        case SourceBlendingFactor::ONE_MINUS_SOURCE_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case SourceBlendingFactor::DESTINATION_ALPHA:
            return GL_DST_ALPHA;
        case SourceBlendingFactor::ONE_MINUS_DESTINATION_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case SourceBlendingFactor::DESTINATION_COLOR:
            return GL_DST_COLOR;
        case SourceBlendingFactor::ONE_MINUS_DESTINATION_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case SourceBlendingFactor::SOURCE_ALPHA_SATURATE:
            return GL_SRC_ALPHA_SATURATE;
        case SourceBlendingFactor::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case SourceBlendingFactor::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case SourceBlendingFactor::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case SourceBlendingFactor::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
    }
}

inline GLenum toDestinationBlendingFactor(DestinationBlendingFactor factor) {
    switch (factor) {
        case DestinationBlendingFactor::ZERO:
            return GL_ZERO;
        case DestinationBlendingFactor::ONE:
            return GL_ONE;
        case DestinationBlendingFactor::SOURCE_COLOR:
            return GL_SRC_COLOR;
        case DestinationBlendingFactor::ONE_MINUS_SOURCE_COLOR:
            return GL_ONE_MINUS_SRC_COLOR;
        case DestinationBlendingFactor::SOURCE_ALPHA:
            return GL_SRC_ALPHA;
        case DestinationBlendingFactor::ONE_MINUS_SOURCE_ALPHA:
            return GL_ONE_MINUS_SRC_ALPHA;
        case DestinationBlendingFactor::DESTINATION_ALPHA:
            return GL_DST_ALPHA;
        case DestinationBlendingFactor::ONE_MINUS_DESTINATION_ALPHA:
            return GL_ONE_MINUS_DST_ALPHA;
        case DestinationBlendingFactor::DESTINATION_COLOR:
            return GL_DST_COLOR;
        case DestinationBlendingFactor::ONE_MINUS_DESTINATION_COLOR:
            return GL_ONE_MINUS_DST_COLOR;
        case DestinationBlendingFactor::CONSTANT_COLOR:
            return GL_CONSTANT_COLOR;
        case DestinationBlendingFactor::ONE_MINUS_CONSTANT_COLOR:
            return GL_ONE_MINUS_CONSTANT_COLOR;
        case DestinationBlendingFactor::CONSTANT_ALPHA:
            return GL_CONSTANT_ALPHA;
        case DestinationBlendingFactor::ONE_MINUS_CONSTANT_ALPHA:
            return GL_ONE_MINUS_CONSTANT_ALPHA;
    }
}

inline GLenum toDepthFunction(DepthTestFunction func) {
    switch (func) {
        case DepthTestFunction::NEVER:
            return GL_NEVER;
        case DepthTestFunction::LESS:
            return GL_LESS;
        case DepthTestFunction::EQUAL:
            return GL_EQUAL;
        case DepthTestFunction::LESSTHAN_OR_EQUAL:
            return GL_LEQUAL;
        case DepthTestFunction::GREATER:
            return GL_GREATER;
        case DepthTestFunction::NOT_EQUAL:
            return GL_NOTEQUAL;
        case DepthTestFunction::GREATERTHAN_OR_EQUAL:
            return GL_GEQUAL;
        case DepthTestFunction::ALWAYS:
            return GL_ALWAYS;
    }
}

inline GLenum toIndexBufferType(IndexBufferType type) {
    switch (type) {
        case IndexBufferType::U_SHORT:
            return GL_UNSIGNED_SHORT;
        case IndexBufferType::U_INT:
            return GL_UNSIGNED_INT;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr