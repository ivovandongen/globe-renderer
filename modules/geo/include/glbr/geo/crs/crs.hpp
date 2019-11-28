#pragma once

#include <glbr/geo/lng_lat.hpp>

namespace glbr {
namespace geo {
namespace crs {

class CRS {
public:
    virtual ~CRS() = default;
    virtual core::geometry::Point2D<double> lngLatToPoint(LngLat lngLat, float zoom) const  = 0;
    virtual LngLat pointToLatLng(const core::geometry::Point2D<double>& point, double zoom) const  = 0;
    virtual int tileSize() const = 0;
};

}  // namespace crs
}  // namespace geo
}  // namespace glbr