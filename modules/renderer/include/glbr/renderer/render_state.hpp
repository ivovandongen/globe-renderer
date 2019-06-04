#pragma once

#include <glbr/core/geometry/winding_order.hpp>

namespace glbr {
namespace renderer {

enum class RasterizationMode { Point, Line, Fill };

enum class CullFace { FRONT, BACK, FRONT_AND_BACK };

struct FaceCulling {
    bool enabled;
    CullFace cullFace;
    core::geometry::WindingOrder frontFaceWindingOrder;

    bool operator==(const FaceCulling& other) const {
        return enabled == other.enabled && cullFace == other.cullFace &&
               frontFaceWindingOrder == other.frontFaceWindingOrder;
    }

    bool operator!=(const FaceCulling& other) const { return !this->operator==(other); }
};

struct RenderState {
    RasterizationMode rasterizationMode{RasterizationMode::Fill};
    FaceCulling faceCulling{false, CullFace::BACK, core::geometry::WindingOrder::COUNTER_CLOCK_WISE};
};

}  // namespace renderer
}  // namespace glbr