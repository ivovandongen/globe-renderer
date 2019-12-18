#pragma once

#include <functional>
#include <memory>
#include <string>

namespace glbr {
namespace core {

class Image {
public:
    using Data = unsigned char;

    explicit Image(const std::string& path, bool flipOnLoad = true);
    Image(const Data* imageData, size_t len, bool flipOnLoad = true);

    ~Image() = default;

    operator bool() const { return bool(data_); }

    const Data* data() const { return data_.get(); }

    int width() const { return width_; }

    int height() const { return height_; }

    int channels() const { return channels_; }

private:
    int width_{0}, height_{0}, channels_{0};
    std::shared_ptr<Data> data_;
};

}  // namespace core
}  // namespace glbr
