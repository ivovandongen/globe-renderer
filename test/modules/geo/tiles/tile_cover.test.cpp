#include <glbr/geo/crs/epsg_3857.hpp>
#include <glbr/geo/tiles/tile_cover.hpp>

#include <test.hpp>

using namespace glbr::geo;
using namespace glbr::geo::crs;

TEST(TileCover2D, ZeroToTwelve) {
    EPSG3857 crs{512};
    ASSERT_EQ(1, tileCover2D(LngLatBounds{LngLat{-180, -90}, LngLat{180, 90}}, 0, crs).size());
    ASSERT_EQ(4, tileCover2D(LngLatBounds{LngLat{-180, -90}, LngLat{180, 90}}, 1, crs).size());
    ASSERT_EQ(16, tileCover2D(LngLatBounds{LngLat{-180, -90}, LngLat{180, 90}}, 2, crs).size());
    ASSERT_EQ(64, tileCover2D(LngLatBounds{LngLat{-180, -90}, LngLat{180, 90}}, 3, crs).size());
    ASSERT_EQ(16777216, tileCover2D(LngLatBounds{LngLat{-180, -90}, LngLat{180, 90}}, 12, crs).size());
}

TEST(TileCover2D, Partial) {
    EPSG3857 crs{512};
    auto tiles = tileCover2D(LngLatBounds{LngLat{-170, -80}, LngLat{170, 80}}, 1, crs);
    ASSERT_EQ(4, tiles.size());
    std::vector<TileId> expected{{0, 0, 1}, {0, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    ASSERT_EQ(expected, tiles);
}