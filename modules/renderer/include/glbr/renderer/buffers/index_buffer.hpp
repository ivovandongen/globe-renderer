#pragma once

namespace glbr {
namespace renderer {

class IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void bind() = 0;

    virtual void upload(const void* data) = 0;

    virtual unsigned int count() const = 0;
};

}  // namespace renderer
}  // namespace glbr