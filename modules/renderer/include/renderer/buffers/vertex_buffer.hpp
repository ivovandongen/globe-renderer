#pragma once

namespace renderer {

class VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void bind() = 0;

    virtual void upload(void* data) = 0;

    virtual unsigned int size() = 0;
};

}  // namespace renderer