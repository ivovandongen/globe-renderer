#include <glbr/geo/tiles/tile_id.hpp>

#include <test.hpp>

using namespace glbr::geo;

TEST(TileId, MaxIndexForZoom) {
    ASSERT_EQ(0, TileId::MaxIndexForZoom(0));
    ASSERT_EQ(1, TileId::MaxIndexForZoom(1));
    ASSERT_EQ(3, TileId::MaxIndexForZoom(2));
    ASSERT_EQ(7, TileId::MaxIndexForZoom(3));
    ASSERT_EQ(4095, TileId::MaxIndexForZoom(12));
}

TEST(TileId, Wrapping) {
    // Wrap on X axis
    auto tile = TileId::UnWrap(1, 0, 0);
    ASSERT_EQ(tile.x(), 0);
    ASSERT_EQ(tile.y(), 0);
    ASSERT_EQ(tile.wrapsX(), 1);
    ASSERT_EQ(tile.wrapsY(), 0);

    // Wrap on both axis
    tile = TileId::UnWrap(1, 1, 0);
    ASSERT_EQ(tile.x(), 0);
    ASSERT_EQ(tile.y(), 0);
    ASSERT_EQ(tile.wrapsX(), 1);
    ASSERT_EQ(tile.wrapsY(), 1);

    // Wrap on higher zoom level
    tile = TileId::UnWrap(2, 2, 1);
    ASSERT_EQ(tile.x(), 0);
    ASSERT_EQ(tile.y(), 0);
    ASSERT_EQ(tile.wrapsX(), 1);
    ASSERT_EQ(tile.wrapsY(), 1);
    
    // Negative wrap
    tile = TileId::UnWrap(-1, -1, 1);
    ASSERT_EQ(tile.x(), 1);
    ASSERT_EQ(tile.y(), 1);
    ASSERT_EQ(tile.wrapsX(), -1);
    ASSERT_EQ(tile.wrapsY(), -1);

    // No wrap
    tile = TileId::UnWrap(1, 1, 1);
    ASSERT_EQ(tile.x(), 1);
    ASSERT_EQ(tile.y(), 1);
    ASSERT_EQ(tile.wrapsX(), 0);
    ASSERT_EQ(tile.wrapsY(), 0);

}