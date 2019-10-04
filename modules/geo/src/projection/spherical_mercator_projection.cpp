#include <glbr/geo/projection/spherical_mercator_projection.hpp>

#include <glbr/core/algorithm.hpp>
#include <glbr/core/maths.hpp>

#include <cmath>

namespace glbr {
namespace geo {
namespace projection {

using namespace glbr::core;

geometry::Point2D<double> SphericalMercatorProjection::project(const LngLat& coord) const {
    auto lat = clamp(coord.lat(), -MAX_LATITUDE, MAX_LATITUDE);
    auto sin = std::sin(deg2rad(lat));

    return {RADIUS * deg2rad(coord.lng()), RADIUS * std::log((1 + sin) / (1 - sin)) / 2};
}

LngLat SphericalMercatorProjection::unproject(const geometry::Point2D<double>& point) const {
    return {rad2deg(point.x()) / RADIUS, rad2deg(2 * std::atan(std::exp(point.y() / RADIUS)) - (M_PI / 2))};
}

}  // namespace projection
}  // namespace geo
}  // namespace glbr