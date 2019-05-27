#include <glbr/core/image.hpp>

#include <glbr/logging/logging.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace glbr {
namespace core {

Image::Image(const std::string &path, bool flipOnLoad) {
    logging::debug("Loading image: {} flipped: {}", path, flipOnLoad);

    stbi_set_flip_vertically_on_load(flipOnLoad);

    _data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    if (!_data) {
        logging::debug("Could not read file: {} flipped: {}", path);
        throw std::runtime_error{std::string{"Could not read file: "} + path};
    }
}

Image::~Image() {
    stbi_image_free(_data);
}

}  // namespace core
}  // namespace glbr
