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

std::array<core::geometry::Point2D<double>, 2> toPixelBounds(const LngLatBounds& bounds, int z, const crs::CRS& crs) {
    return {crs.lngLatToPoint(bounds.nw(), z), crs.lngLatToPoint(bounds.se(), z)};
}

std::vector<TileId> tileCover2D(const LngLatBounds& bounds, int z, const crs::CRS& crs) {
    // Determine bounds in pixels
    auto pixelBounds = toPixelBounds(bounds, z, crs);

    // Convert bounds in pixels to bounds in tiles (divide by tile size)
    std::array<core::geometry::Point2D<double>, 2> tileBounds{pixelBounds[0] / crs.tileSize(),
                                                              pixelBounds[1] / crs.tileSize()};

    // Iterate over bounds to get tiles
    auto minX = static_cast<int>(tileBounds[0].x());
    auto maxX = static_cast<int>(std::ceil(tileBounds[1].x()));
    auto minY = static_cast<int>(tileBounds[0].y());
    auto maxY = static_cast<int>(std::ceil(tileBounds[1].y()));
    std::vector<TileId> tiles;
    for (int x = minX; x < maxX; x++) {
        for (int y = minY; y < maxY; y++) {
            tiles.emplace_back(x, y, z);
        }
    }

    // TODO sort

    return tiles;
}

}  // namespace geo
}  // namespace glbr
