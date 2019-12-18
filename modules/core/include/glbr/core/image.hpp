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

    operator bool() const { return bool(_data); }

    const Data* data() const { return _data.get(); }

    int width() const { return _width; }

    int height() const { return _height; }

    int channels() const { return _channels; }

private:
    int _width{0}, _height{0}, _channels{0};
    std::shared_ptr<Data> _data;
};

}  // namespace core
}  // namespace glbr
