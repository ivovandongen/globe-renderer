#pragma once

#include <cstdint>

namespace glbr {
namespace renderer {

enum class IndexBufferType { U_SHORT, U_INT };

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual IndexBufferType type() = 0;

    virtual void bind() = 0;

    virtual void upload(const void* data) = 0;

    virtual void upload(const void* data, uint32_t count) = 0;

    virtual unsigned int count() const = 0;
};

}  // namespace renderer
}  // namespace glbr