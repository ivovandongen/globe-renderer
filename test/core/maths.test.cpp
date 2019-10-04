#include <test.hpp>

#include <glbr/core/maths.hpp>

#include <vector>

using namespace glbr::core;

TEST(Maths, deg2rad) {
    ASSERT_FLOAT_EQ(deg2rad(180.), M_PI);
    ASSERT_FLOAT_EQ(deg2rad(360.), 2 * M_PI);
    ASSERT_FLOAT_EQ(deg2rad(-360.), -2 * M_PI);
}

TEST(Maths, rad2deg) {
    ASSERT_FLOAT_EQ(rad2deg(M_PI), 180);
    ASSERT_FLOAT_EQ(rad2deg(2 * M_PI), 360);
    ASSERT_FLOAT_EQ(rad2deg(-2 * M_PI), -360);
}