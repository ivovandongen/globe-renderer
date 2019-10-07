#include <glbr/geo/crs/epsg_3857.hpp>

#include <cmath>

namespace {
using namespace glbr::geo::crs;

Transformation<double> createTransformation() {
    auto scale = 0.5 / (M_PI * glbr::geo::projection::SphericalMercatorProjection::RADIUS);
    return {scale, 0.5, -scale, 0.5};
}

}  // namespace

namespace glbr {
namespace geo {
namespace crs {

EPSG3857::EPSG3857(int tileSize) : transformation_(createTransformation()), tileSize_(tileSize) {}

double EPSG3857::scale(double zoom) const {
    return std::pow(2.0, zoom) * tileSize_;
}

double EPSG3857::zoom(double scale) const {
    return std::log2(scale / tileSize_);
}

core::geometry::Point2D<double> EPSG3857::lngLatToPoint(LngLat lngLat, float zoom) const {
    auto projectedPoint = projection_.project(lngLat);
    auto scale = this->scale(zoom);

    return transformation_.transform(projectedPoint, scale);
}

LngLat EPSG3857::pointToLatLng(const core::geometry::Point2D<double>& point, double zoom) const {
    auto scale = this->scale(zoom);
    auto untransformedPoint = transformation_.untransform(point, scale);

    return projection_.unproject(untransformedPoint);
}

}  // namespace crs
}  // namespace geo
}  // namespace glbr
