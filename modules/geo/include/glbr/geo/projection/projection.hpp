#pragma once

#include <glbr/core/geometry/point_3d.hpp>
#include <glbr/geo/lng_lat.hpp>

namespace glbr {
namespace geo {
namespace projection {

template <class Point = core::geometry::Point2D<double>>
class Projection {
public:
    virtual ~Projection() = default;
    virtual Point project(const LngLat&) const = 0;
    virtual LngLat unproject(const Point&) const = 0;
};

}  // namespace projection
}  // namespace geo
}  // namespace glbr