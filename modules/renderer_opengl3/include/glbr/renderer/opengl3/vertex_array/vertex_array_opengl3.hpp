#pragma once

#include <glbr/renderer/opengl3/buffers/index_buffer_opengl3.hpp>
#include <glbr/renderer/opengl3/vertex_buffer_attributes/vertex_buffer_attribute_bindings_opengl3.hpp>
#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

#include <memory>
#include <utility>
#include <vector>

using namespace std::rel_ops;

namespace glbr {
namespace renderer {
namespace opengl3 {

class ContextOpenGL3;

class VertexArrayOpenGL3 : public VertexArray, public std::enable_shared_from_this<VertexArrayOpenGL3> {
public:
    explicit VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3>);

    VertexArrayOpenGL3(std::shared_ptr<ContextOpenGL3>, std::unique_ptr<IndexBufferOpenGL3>);

    ~VertexArrayOpenGL3() override;

    IndexBufferOpenGL3 *indexBuffer() override;

    void indexBuffer(std::shared_ptr<IndexBuffer>) override;

    void clean(const Pipeline &pipeline);

    void add(const std::string &key, VertexBufferAttribute attribute) override;

    uint32_t id() const { return _id; }

    bool operator==(const VertexArrayOpenGL3 &other) { return _id == other._id; }
    bool operator!=(const VertexArrayOpenGL3 &other) { return !(*this == other); }

    void bind() override;

    void unbind() override;

private:
    uint32_t _id{0};
    std::shared_ptr<ContextOpenGL3> _context;
    std::shared_ptr<IndexBufferOpenGL3> _indexBuffer;
    VertexBufferAttributeBindingsOpenGL3 _attributes;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr