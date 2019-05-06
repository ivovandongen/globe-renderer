#pragma once

#include <glad/glad.h>
#include <glbr/renderer/opengl3/buffers/index_buffer_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_attributes/vertex_attribute_bindings_opengl3.hpp>
#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

#include <vector>

namespace glbr {
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

    void clean(const Pipeline &pipeline);

    void unbind();

    void add(const std::string &key, VertexAttribute attribute) override;

private:
    GLuint _id{0};
    std::unique_ptr<IndexBufferOpenGL3> _indexBuffer;
    VertexAttributeBindingsOpenGL3 _attributes;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr