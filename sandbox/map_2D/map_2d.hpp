#pragma once

#include <glbr/core/algorithm.hpp>
#include <glbr/core/image.hpp>
#include <glbr/geo/crs/epsg_3857.hpp>
#include <glbr/geo/lng_lat_bounds.hpp>
#include <glbr/io/data_source.hpp>

#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>

namespace glbr {

// TODO: implement Renderable
class Tile {
public:
    Tile(geo::TileId id, std::shared_ptr<io::DataSource> dataSource, const std::string& accessToken)
        : id_(id), dataSource_(std::move(dataSource)) {
        const constexpr static char* url_pattern =
            "https://api.mapbox.com/v4/mapbox.satellite/%d/%d/%d@2x.png?"
            "access_token=%s"
            "S0KL6oRTIrz12tQw1etMcg";

        char* url;
        asprintf(&url, url_pattern, id_.z(), id_.x(), id_.y(), accessToken.c_str());
        auto resource = io::Resource{url};
        tileRequest_ = dataSource_->load(resource, [this](const io::DataSource::ResponseHolder& response) {
            if (!response) {
                logging::debug(
                    "Could not load tile {}/{}/{}: {}", id_.x(), id_.y(), id_.z(), response.error().message());
            } else {
                logging::debug("Loaded tile {}/{}/{}", id_.x(), id_.y(), id_.z());
                loaded_ = true;
                try {
                    image_ = std::make_unique<core::Image>(
                        (core::Image::Data*)response->data().data(), response->data().size(), false);
                } catch (...) {
                    loaded_ = false;
                }
            }

            // XXX
            tileRequest_.reset();
        });
    }

    virtual ~Tile() { logging::info("Destroying tile {}/{}/{}", id_.x(), id_.y(), id_.z()); }

    const geo::TileId& id() const { return id_; }

    bool loaded() const { return loaded_; }

    void upload(renderer::Context& context) {
        if (!loaded_) {
            return;
        }

        if (!texture_ && image_) {
            logging::debug("Uploading texture for {}/{}/{}", id_.x(), id_.y(), id_.z());
            texture_ = context.device().createTexture2D(*image_, true);
        }
    }

    void render(renderer::Context& context, renderer::SceneState& sceneState) {}

    bool operator==(const Tile& rhs) { return id_ == rhs.id(); }
    bool operator!=(const Tile& rhs) { return !operator==(rhs); }

private:
    geo::TileId id_;
    bool loaded_{false};
    std::shared_ptr<io::DataSource> dataSource_;
    std::unique_ptr<io::AsyncRequest> tileRequest_;
    std::unique_ptr<core::Image> image_;
    std::unique_ptr<renderer::Texture2D> texture_;
};

class TileCover {
public:
    TileCover(geo::crs::CRS& crs, std::shared_ptr<io::DataSource> dataSource, std::string accessToken)
        : crs_(crs), dataSource_(std::move(dataSource)), accessToken_(std::move(accessToken)) {}

    void update(const geo::LngLatBounds& bounds, double zoom) {
        // TODO  Very crude
        tiles_.clear();
        auto cover = geo::tileCover2D(bounds, floor(zoom), crs_);
        for (const auto& id : cover) {
            logging::debug("Loading tile {}/{}/{}", id.x(), id.y(), id.z());
            tiles_.push_back(std::make_unique<Tile>(id, dataSource_, accessToken_));
        }
    }

    const std::vector<std::unique_ptr<Tile>>& tiles() { return tiles_; }

private:
    geo::crs::CRS& crs_;
    std::shared_ptr<io::DataSource> dataSource_;
    std::vector<std::unique_ptr<Tile>> tiles_;
    std::string accessToken_;
};

class Map2D {
public:
    Map2D(float width,
          float height,
          std::shared_ptr<io::DataSource> dataSource,
          std::string accessToken,
          double zoom = 0,
          int tileSize = 512)
        : dataSource_(std::move(dataSource)),
          tileSize_(tileSize),
          crs_(tileSize),
          width_(width),
          height_(height),
          zoom_(zoom),
          center_(0, 0),
          cover_(crs_, dataSource_, std::move(accessToken)) {
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
            cover_.update(bounds(), zoom());
            dirty_ = false;
        }
    }

    void render(renderer::Context& context, renderer::SceneState& sceneState) {
        // Upload data
        for (auto& tile : cover_.tiles()) {
            if (tile->loaded()) {
                tile->upload(context);
            }
        }

        // Render
        for (auto& tile : cover_.tiles()) {
            if (tile->loaded()) {
                tile->render(context, sceneState);
            }
        }
    }

private:
    void constrain() {
        zoom_ = std::max<double>(zoom_, minZoom());
        center_.lng() = core::clamp<double>(center_.lng(), -180, +180);
        center_.lat() = core::clamp<double>(center_.lng(), -crs_.MaxLatitude(), crs_.MaxLatitude());
    }

private:
    std::shared_ptr<io::DataSource> dataSource_;
    bool dirty_ = true;
    double tileSize_;
    geo::crs::EPSG3857 crs_;

    double zoom_;
    geo::LngLat center_;
    float width_;
    float height_;

    TileCover cover_;
};

}  // namespace glbr
