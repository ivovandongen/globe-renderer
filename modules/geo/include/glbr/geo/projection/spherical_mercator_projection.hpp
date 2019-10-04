#pragma once

#include "projection.hpp"

namespace glbr {
namespace geo {
namespace projection {

class SphericalMercatorProjection : public Projection<core::geometry::Point2D<double>> {
public:
    const constexpr static double MAX_LATITUDE = 85.0511287798;
    const constexpr static double RADIUS = 6378137;

    core::geometry::Point2D<double> project(const LngLat& lat) const override;
    LngLat unproject(const core::geometry::Point2D<double>& d) const override;
};

}  // namespace projection
}  // namespace geo
}  // namespace glbr