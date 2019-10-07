#include <glbr/geo/crs/epsg_3857.hpp>

#include <test.hpp>

using namespace glbr::core::geometry;
using namespace glbr::geo;
using namespace glbr::geo::crs;

template <class P1, class P2>
inline void assertNear(const P1& a, const P2& b, double error = 0.001) {
    ASSERT_NEAR(a.x(), b.x(), error);
    ASSERT_NEAR(a.y(), b.y(), error);
}

TEST(EPSG3857, scale) {
    EPSG3857 crs(256);
    ASSERT_NEAR(crs.scale(2.5), 1448.15, .01);
}

TEST(EPSG3857, zoom) {
    EPSG3857 crs(256);
    ASSERT_NEAR(crs.zoom(1448.15), 2.5, .01);
}

TEST(EPSG3857, zoomScale) {
    EPSG3857 crs(256);
    ASSERT_NEAR(crs.zoom(crs.scale(0)), 0, .01);
    ASSERT_NEAR(crs.scale(crs.zoom(0)), 0, .01);
}

TEST(EPSG3857, lngLatToPoint) {
    EPSG3857 crs(256);
    assertNear(crs.lngLatToPoint(LngLat(0, 0), 0), Point2D<double>(128, 128));
    assertNear(crs.lngLatToPoint(LngLat(180, EPSG3857::MaxLatitude()), 0), Point2D<double>(256, 0));

    EPSG3857 crs_512(512);
    assertNear(crs_512.lngLatToPoint(LngLat(-180, EPSG3857::MaxLatitude()), 0), Point2D<double>(0, 0));
    assertNear(crs_512.lngLatToPoint(LngLat(180, -EPSG3857::MaxLatitude()), 0), Point2D<double>(512, 512));
}

TEST(EPSG3857, pointToLngLatZoom) {
    EPSG3857 crs(512);
    assertNear(crs.pointToLatLng(Point2D<double>(0, 0), 1), LngLat(-180, EPSG3857::MaxLatitude()));
    assertNear(crs.pointToLatLng(Point2D<double>(512, 512), 1), LngLat(0, 0));
    assertNear(crs.pointToLatLng(Point2D<double>(512, 512), 22), LngLat(-179.9999, 85.0511));
}

TEST(EPSG3857, lngLatToPointZoom) {
    EPSG3857 crs(512);
    assertNear(crs.lngLatToPoint(LngLat(-180, EPSG3857::MaxLatitude()), 1), Point2D<double>(0, 0));
    assertNear(crs.lngLatToPoint(LngLat(0., 0), 1), Point2D<double>(512, 512));
    assertNear(crs.lngLatToPoint(LngLat(180, -EPSG3857::MaxLatitude()), 1), Point2D<double>(1024, 1024));
}