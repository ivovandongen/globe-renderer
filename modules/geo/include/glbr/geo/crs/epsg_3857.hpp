#pragma once

#include <glbr/core/geometry/point_3d.hpp>
#include <glbr/geo/crs/crs.hpp>
#include <glbr/geo/crs/transformation.hpp>
#include <glbr/geo/lng_lat.hpp>
#include <glbr/geo/projection/spherical_mercator_projection.hpp>

#include <functional>

namespace glbr {
namespace geo {
namespace crs {

class EPSG3857 : public CRS {
public:
    explicit EPSG3857(int tileSize = 512);
    ~EPSG3857() override = default;

    core::geometry::Point2D<double> lngLatToPoint(LngLat lngLat, float zoom) const override;

    LngLat pointToLatLng(const core::geometry::Point2D<double>& point, double zoom) const override;

    /**
     * @param zoom the zoom level [0,)
     * @return the map scale [1,) (or the number of tiles per axis
     */
    double scale(double zoom) const;

    double zoom(double scale) const;

    /**
     * @param the scale
     * @return the pixel width at given scale
     */
    double worldSize(double scale) const;

    constexpr static float MaxLatitude() { return projection::SphericalMercatorProjection::MAX_LATITUDE; }

    int tileSize() const override;

private:
    projection::SphericalMercatorProjection projection_;
    Transformation<double> transformation_;
    int tileSize_;
};

}  // namespace crs
}  // namespace geo
}  // namespace glbr