#pragma once

#include <glbr/core/geometry/point_2d.hpp>
#include <glbr/geo/crs/crs.hpp>
#include <glbr/geo/lng_lat.hpp>
#include <glbr/geo/lng_lat_bounds.hpp>
#include <glbr/geo/tiles/tile_id.hpp>

#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

namespace glbr {
namespace geo {

std::array<core::geometry::Point2D<double>, 2> toPixelBounds(const LngLatBounds& bounds,
                                                             uint32_t z,
                                                             const crs::CRS& crs) {
    return {crs.lngLatToPoint(bounds.nw(), z), crs.lngLatToPoint(bounds.se(), z)};
}

std::vector<TileId> tileCover2D(const LngLatBounds& bounds, uint32_t z, const crs::CRS& crs, bool wrap = false) {
    // Determine bounds in pixels
    auto pixelBounds = toPixelBounds(bounds, z, crs);

    // Convert bounds in pixels to bounds in tiles (divide by tile size)
    std::array<core::geometry::Point2D<double>, 2> tileBounds{pixelBounds[0] / crs.tileSize(),
                                                              pixelBounds[1] / crs.tileSize()};

    // Iterate over bounds to get tiles
    auto minX = static_cast<int>(std::floor(tileBounds[0].x()));
    auto maxX = static_cast<int>(std::ceil(tileBounds[1].x()));
    auto minY = static_cast<int>(std::floor(tileBounds[0].y()));
    auto maxY = static_cast<int>(std::ceil(tileBounds[1].y()));

    std::vector<TileId> tiles;
    if (!wrap) {
        uint32_t maxIndex = TileId::MaxIndexForZoom(z);
        minX = core::clamp<int>(minX, 0, maxIndex);
        maxX = core::clamp<int>(maxX, 0, maxIndex);
        minY = core::clamp<int>(minY, 0, maxIndex);
        maxY = core::clamp<int>(maxY, 0, maxIndex);

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                tiles.emplace_back(x, y, z);
            }
        }
    } else {
        for (int x = minX; x < maxX; x++) {
            for (int y = minY; y < maxY; y++) {
                tiles.push_back(TileId::UnWrap(x, y, z));
            }
        }
    }

    // TODO sort by distance from center / focal point

    // Erase duplicates
    tiles.erase(std::unique(tiles.begin(), tiles.end()), tiles.end());

    return tiles;
}

}  // namespace geo
}  // namespace glbr
