#pragma once

#include <glbr/geo/lng_lat.hpp>

namespace glbr {
namespace geo {

class LngLatBounds {
public:
    LngLatBounds(LngLat sw, LngLat ne) : sw_(sw), ne_(ne) {}

    const LngLat& ne() const { return ne_; }
    LngLat se() const { return {ne_.lng(), sw_.lat(), ne_.alt() + sw_.alt() / 2}; }
    const LngLat& sw() const { return sw_; }
    LngLat nw() const { return {sw_.lng(), ne_.lat(), ne_.alt() + sw_.alt() / 2}; }

    static LngLatBounds World() { return {{180, -90}, {-180, 90}}; }

private:
    LngLat sw_;
    LngLat ne_;
};

}  // namespace geo
}  // namespace glbr
