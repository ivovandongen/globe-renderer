#pragma once

#include <glbr/core/geometry/winding_order.hpp>
#include <glbr/renderer/state/blending.hpp>
#include <glbr/renderer/state/depth_test.hpp>
#include <glbr/renderer/state/scissor_test.hpp>

namespace glbr {
namespace renderer {

enum class RasterizationMode { POINT, LINE, FILL };

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
    RasterizationMode rasterizationMode{RasterizationMode::FILL};
    FaceCulling faceCulling{false, CullFace::BACK, core::geometry::WindingOrder::COUNTER_CLOCK_WISE};
    ScissorTest scissorTest;
    Blending blending;
    DepthTest depthTest;
};

}  // namespace renderer
}  // namespace glbr