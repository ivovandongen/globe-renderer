#pragma once

namespace glbr {
namespace renderer {

enum class TextureMinificationFilter {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    LINEAR_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,
};

}  // namespace renderer
}  // namespace glbr