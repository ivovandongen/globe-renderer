#include <glbr/geo/lng_lat_bounds.hpp>

#include <test.hpp>

using namespace glbr::geo;

TEST(LngLatBounds, Basic) {
    LngLatBounds bounds{{-180, -90}, {180, 90}};
    ASSERT_EQ(-180, bounds.sw().lng());
    ASSERT_EQ(-180, bounds.nw().lng());
    ASSERT_EQ(180, bounds.ne().lng());
    ASSERT_EQ(180, bounds.ne().lng());
    ASSERT_EQ(90, bounds.nw().lat());
    ASSERT_EQ(90, bounds.ne().lat());
    ASSERT_EQ(-90, bounds.sw().lat());
    ASSERT_EQ(-90, bounds.se().lat());
}