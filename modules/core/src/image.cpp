#include <glbr/core/image.hpp>

#include <glbr/logging/logging.hpp>

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

namespace glbr {
namespace core {

Image::Image(const std::string& path, bool flipOnLoad) {
    logging::debug("Loading image: {} flipped: {}", path, flipOnLoad);

    stbi_set_flip_vertically_on_load(flipOnLoad);

    auto data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
    if (!data) {
        logging::debug("Could not read file: {} flipped: {}", path);
        throw std::runtime_error{std::string{"Could not read file: "} + path};
    }
    _data = std::shared_ptr<Data>(data, [](Data* ptr) { stbi_image_free(ptr); });
}

Image::Image(const Data* imageData, size_t len, bool flipOnLoad) {
    stbi_set_flip_vertically_on_load(flipOnLoad);
    auto data = stbi_load_from_memory(imageData, len, &_width, &_height, &_channels, 0);
    if (!data) {
        logging::debug("Could not read image from memory");
        throw std::runtime_error{std::string{"Could not read image from memory"}};
    }
    _data = std::shared_ptr<Data>(data, [](Data* ptr) { stbi_image_free(ptr); });
}

}  // namespace core
}  // namespace glbr
