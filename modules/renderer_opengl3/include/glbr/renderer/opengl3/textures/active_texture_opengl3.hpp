#pragma once

#include <cstdint>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ActiveTextureUnitOpenGL3 {
public:
    explicit ActiveTextureUnitOpenGL3(uint8_t index) : index_(index) {}

    uint8_t index() const { return index_; }

    bool operator==(const ActiveTextureUnitOpenGL3 &other) { return index_ == other.index_; }
    bool operator!=(const ActiveTextureUnitOpenGL3 &other) { return !(*this == other); }

private:
    uint8_t index_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr