#pragma once

#include <glbr/core/algorithm.hpp>
#include <glbr/geo/crs/epsg_3857.hpp>
#include <glbr/geo/lng_lat_bounds.hpp>

#include <algorithm>
#include <iostream>

namespace glbr {

class Map2D {
public:
    Map2D(float width, float height, double zoom = 0, int tileSize = 512)
        : tileSize_(tileSize), crs_(tileSize), width_(width), height_(height), zoom_(zoom), center_(0, 0) {
        constrain();
    }

    void resize(float width, float height) {
        if (width == width_ && height == height_) {
            return;
        }

        width_ = width;
        height_ = height;
        constrain();
        dirty_ = true;
    }

    geo::LngLatBounds bounds() const {
        auto centerW = crs_.lngLatToPoint(center_, zoom_);
        return {crs_.pointToLatLng({centerW.x() - width_ / 2, centerW.y() + height_ / 2}, zoom_),
                crs_.pointToLatLng({centerW.x() + width_ / 2, centerW.y() - height_ / 2}, zoom_)};
    }

    double zoom() const { return zoom_; }

    void zoom(double zoom) {
        zoom = core::clamp<double>(zoom, 0, 22);
        if (zoom == zoom_) {
            return;
        }
        zoom_ = zoom;
        constrain();
        dirty_ = true;
    }

    double minZoom() const { return std::max(0., std::log2(height_ / tileSize_)); }

    void move(float x, float y) {
        center_.x() += x;
        center_.y() += y;
        constrain();
        dirty_ = true;
    }

    void center(const geo::LngLat& center) {
        if (center_ == center) {
            return;
        }
        center_ = center;
        dirty_ = true;
    }

    const geo::LngLat& center() const { return center_; }

    void update() {
        if (dirty_) {
            auto cover = geo::tileCover2D(bounds(), zoom(), crs_);
            std::cout << "Tiles { ";
            for (auto& tile : cover) {
                std::cout << tile.x() << "/" << tile.y() << "/" << tile.z() << " ";
            }
            std::cout << "}" << std::endl;
            dirty_ = false;
        }
    }

    void render(renderer::Context& context) {}

private:
    void constrain() {
        zoom_ = std::max<double>(zoom_, minZoom());
        center_.lng() = core::clamp<double>(center_.lng(), -180, +180);
        center_.lat() = core::clamp<double>(center_.lng(), -crs_.MaxLatitude(), crs_.MaxLatitude());
    }

private:
    bool dirty_ = true;
    double tileSize_;
    geo::crs::EPSG3857 crs_;

    double zoom_;
    geo::LngLat center_;
    float width_;
    float height_;
};

}  // namespace glbr
