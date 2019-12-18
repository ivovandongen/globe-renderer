#pragma once

#include <glbr/core/algorithm.hpp>

#include <cmath>

namespace glbr {
namespace geo {

class TileId {
public:
    static inline constexpr uint32_t MaxTilesPerAxisForZoom(uint32_t z) { return (1ull << z); }
    static inline constexpr uint32_t MaxIndexForZoom(uint32_t z) { return MaxTilesPerAxisForZoom(z) - 1; }

    static TileId UnWrap(int x, int y, uint32_t z) {
        int maxTiles = MaxTilesPerAxisForZoom(z);
        int wrapsX = (x < 0 ? x - maxTiles + 1 : x) / maxTiles;
        int wrapsY = (y < 0 ? y - maxTiles + 1 : y) / maxTiles;

        return {static_cast<uint32_t>(x - wrapsX * maxTiles),
                static_cast<uint32_t>(y - wrapsY * maxTiles),
                z,
                wrapsX,
                wrapsY};
    }

    TileId(uint32_t x, uint32_t y, uint32_t z, int wrapsX = 0, int wrapsY = 0)
        : x_(x), y_(y), z_(z), wrapsX_(wrapsX), wrapsY_(wrapsY) {
        assert(x <= MaxIndexForZoom(z));
        assert(y <= MaxIndexForZoom(z));
    }

    inline int x() const { return x_; }
    inline int y() const { return y_; }
    inline uint32_t z() const { return z_; }
    inline int wrapsX() const { return wrapsX_; }
    inline int wrapsY() const { return wrapsY_; }

private:
    uint32_t x_;
    uint32_t y_;
    uint32_t z_;
    int wrapsX_;
    int wrapsY_;
};

inline bool operator==(const TileId& lhs, const TileId& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() && lhs.wrapsX() == rhs.wrapsX() &&
           lhs.wrapsY() == rhs.wrapsY();
}

}  // namespace geo
}  // namespace glbr
