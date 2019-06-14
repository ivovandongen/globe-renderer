#include <test.hpp>

#include <glbr/core/maths.hpp>

#include <vector>

using namespace glbr::core;

TEST(Maths, rad2deg) {
    ASSERT_FLOAT_EQ(deg2rad(180), M_PI);
}