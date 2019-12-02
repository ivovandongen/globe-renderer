#include <test.hpp>

#include <glbr/core/image.hpp>

#include <vector>

using namespace glbr::core;

TEST(Image, Basic) {
    Image image{"resources/kitty.png"};
    ASSERT_EQ(225, image.height());
    ASSERT_EQ(225, image.width());
    ASSERT_EQ(3, image.channels());
}