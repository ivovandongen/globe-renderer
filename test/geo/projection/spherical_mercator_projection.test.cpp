#include <glbr/geo/projection/spherical_mercator_projection.hpp>

#include <test.hpp>

using namespace glbr::core::geometry;
using namespace glbr::geo;
using namespace glbr::geo::projection;

template <class P1, class P2>
void assertNear(const P1& a, const P2& b, double error) {
    ASSERT_NEAR(a.x(), b.x(), error);
    ASSERT_NEAR(a.y(), b.y(), error);
}

TEST(SphericalMercatorProjection, Project) {
    SphericalMercatorProjection projection;

    ASSERT_EQ(Point2D<double>(0, 0), projection.project({0, 0}));
    assertNear(
        Point2D<double>(20037508, 20037508), projection.project({180, SphericalMercatorProjection::MAX_LATITUDE}), 1);
    assertNear(Point2D<double>(-20037508, -20037508),
               projection.project({-180, -SphericalMercatorProjection::MAX_LATITUDE}),
               1);
}

TEST(SphericalMercatorProjection, Unproject) {
    SphericalMercatorProjection projection;

    ASSERT_EQ(Point2D<double>(0, 0), projection.project({0, 0}));
    assertNear(LngLat{180, SphericalMercatorProjection::MAX_LATITUDE},
               projection.unproject(Point2D<double>(20037508, 20037508)),
               1);
    assertNear(LngLat{-180, -SphericalMercatorProjection::MAX_LATITUDE},
               projection.unproject(Point2D<double>(-20037508, -20037508)),
               1);
}