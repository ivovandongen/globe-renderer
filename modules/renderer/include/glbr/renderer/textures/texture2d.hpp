#pragma once

namespace glbr {
namespace renderer {

class Texture2D {
public:
    virtual ~Texture2D() = default;

    virtual void bind() const = 0;

    virtual void upload(const void* data) const = 0;
};

}  // namespace renderer
}  // namespace glbr