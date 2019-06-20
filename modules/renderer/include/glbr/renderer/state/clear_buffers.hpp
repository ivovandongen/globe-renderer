#pragma once

namespace glbr {
namespace renderer {

enum class ClearBuffers : uint8_t {
    COLOR = 1,
    DEPTH = 2,
    STENCIL = 4,
    COLOR_AND_DEPTH = COLOR | DEPTH,
    ALL = uint8_t(COLOR | uint8_t(DEPTH | STENCIL))
};

}  // namespace renderer
}  // namespace glbr