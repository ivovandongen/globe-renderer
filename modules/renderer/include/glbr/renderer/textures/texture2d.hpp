#pragma once

#include <glbr/core/image.hpp>

namespace glbr {
namespace renderer {

class Texture2D {
public:
    virtual ~Texture2D() = default;

    virtual void bind() const = 0;

    virtual void upload(const void* data) const = 0;

    void upload(const core::Image& image) const { upload(image.data()); };
};

}  // namespace renderer
}  // namespace glbr