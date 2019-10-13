#pragma once

#include <glbr/geo/lng_lat.hpp>

namespace glbr {
namespace geo {

class LngLatBounds {
public:
    LngLatBounds(LngLat sw, LngLat ne) : sw_(sw), ne_(ne) {}

    const LngLat& ne() const { return ne_; }
    const LngLat& sw() const { return sw_; }

    static LngLatBounds World() { return {{180, -90}, {-180, 90}}; }

private:
    LngLat sw_;
    LngLat ne_;
};

}  // namespace geo
}  // namespace glbr
