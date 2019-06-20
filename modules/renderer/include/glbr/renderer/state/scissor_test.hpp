#pragma once

namespace glbr {
namespace renderer {

struct Rectangle {
    int x, y, width, height;

    bool operator==(const Rectangle& other) const {
        return other.x == x && other.y == y && other.width == width && other.height == height;
    }

    bool operator!=(const Rectangle& other) const { return !(other == *this); }
};

struct ScissorTest {
    bool enabled{false};
    Rectangle rectangle{0, 0, 0, 0};
};

}  // namespace renderer
}  // namespace glbr
