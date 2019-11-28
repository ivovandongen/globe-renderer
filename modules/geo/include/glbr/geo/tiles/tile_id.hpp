#pragma once

namespace glbr {
namespace geo {

class TileId {
public:
    TileId(int x, int y, int z) : x_(x), y_(y), z_(z) {}

    inline int x() const { return x_; }
    inline int y() const { return y_; }
    inline int z() const { return z_; }

private:
    int x_, y_, z_;
};

inline bool operator==(const TileId& lhs, const TileId& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

}  // namespace geo
}  // namespace glbr
