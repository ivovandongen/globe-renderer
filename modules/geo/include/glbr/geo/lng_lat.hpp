#pragma once

#include <glbr/core/geometry/point_3d.hpp>

namespace glbr {
namespace geo {

class LngLat : public core::geometry::Point3D<double> {
public:
    LngLat(double lng, double lat, double alt) : Point3D(lng, lat, alt) {}
    LngLat(double lng, double lat) : Point3D(lng, lat, 0) {}

    inline double lng() const { return x(); }

    inline double lat() const { return y(); }

    inline double alt() const { return z(); }
};

}  // namespace geo
}  // namespace glbr