#pragma once

#include <glbr/core/geometry/point_3d.hpp>
#include <glbr/geo/crs/transformation.hpp>
#include <glbr/geo/lng_lat.hpp>
#include <glbr/geo/projection/spherical_mercator_projection.hpp>

#include <functional>

namespace glbr {
namespace geo {
namespace crs {

class EPSG3857 {
public:
    EPSG3857(int tileSize = 521);

    core::geometry::Point2D<double> lngLatToPoint(LngLat lngLat, float zoom) const;

    LngLat pointToLatLng(const core::geometry::Point2D<double>& point, double zoom) const;

    double scale(double zoom) const;

    double zoom(double scale) const;

    static constexpr float MaxLatitude() { return projection::SphericalMercatorProjection::MAX_LATITUDE; }

private:
    projection::SphericalMercatorProjection projection_;
    Transformation<double> transformation_;
    int tileSize_;
};

}  // namespace crs
}  // namespace geo
}  // namespace glbr