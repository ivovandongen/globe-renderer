#pragma once

namespace glbr {
namespace renderer {

enum class RasterizationMode { Point, Line, Fill };

struct RenderState {
    RasterizationMode rasterizationMode{RasterizationMode::Fill};
};

}  // namespace renderer
}  // namespace glbr