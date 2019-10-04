#include <glbr/core/algorithm.hpp>

#include <test.hpp>

using namespace glbr::core;

TEST(Algorithm, clamp) {
    ASSERT_EQ(clamp(0, 10, 2), 2);
    ASSERT_EQ(clamp(.1, 0., 1.), .1);
}
