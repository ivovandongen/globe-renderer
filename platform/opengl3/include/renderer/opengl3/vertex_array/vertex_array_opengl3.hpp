#pragma once

#include <glad/glad.h>
#include <renderer/opengl3/buffers/index_buffer_opengl3.hpp>
#include <renderer/vertex_array/vertex_array.hpp>

#include <vector>

namespace renderer {
namespace opengl3 {

class VertexArrayOpenGL3 : public VertexArray {
public:
    VertexArrayOpenGL3();

    explicit VertexArrayOpenGL3(std::unique_ptr<IndexBufferOpenGL3>);

    ~VertexArrayOpenGL3() override;

    IndexBufferOpenGL3 *indexBuffer() override;

    void indexBuffer(std::unique_ptr<IndexBuffer>) override;

    void bind() override;

    void unbind();

    void add(VertexAttribute attribute) override;

private:
    GLuint _id{0};
    std::unique_ptr<IndexBufferOpenGL3> _indexBuffer;
    std::vector<VertexAttribute> _attributes;
    bool _attributesDirty{false};
};

}  // namespace opengl3
}  // namespace renderer