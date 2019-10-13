#pragma once

#include <glbr/core/algorithm.hpp>
#include <glbr/geo/crs/epsg_3857.hpp>
#include <glbr/geo/lng_lat_bounds.hpp>

#include <algorithm>

namespace glbr {

class Map2D {
public:
    Map2D(float width, float height, double zoom = 0, int tileSize = 512)
        : tileSize_(tileSize), crs_(tileSize), width_(width), height_(height), zoom_(zoom) {
        constrain();
    }

    void resize(float width, float height) {
        width_ = width;
        height_ = height;
        constrain();
    }

    geo::LngLatBounds bounds() const {
        return {crs_.pointToLatLng({width_, height_}, zoom_), crs_.pointToLatLng({0, 0}, zoom_)};
    }

    double zoom() const { return zoom_; }

    void zoom(double zoom) {
        zoom_ = core::clamp<double>(zoom, 0, 22);
        constrain();
    }

    double minZoom() const { return std::max(0., std::log2(height_ / tileSize_)); }

private:
    void constrain() { zoom_ = std::max<double>(zoom_, minZoom()); }

private:
    double tileSize_;
    geo::crs::EPSG3857 crs_;

    double zoom_;
    float width_;
    float height_;
};

}  // namespace glbr
