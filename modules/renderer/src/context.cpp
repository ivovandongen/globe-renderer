#include <glbr/renderer/context.hpp>

#include <cassert>

namespace glbr {
namespace renderer {

std::unique_ptr<VertexArray> Context::createVertexArray(const core::geometry::Mesh &mesh) const {
    using namespace core::geometry;

    // TODO BufferHint (2x)

    // Create a vertex array
    auto vertexArray = createVertexArray();
    vertexArray->bind();

    // Add the vertices to the VertexBuffer
    std::shared_ptr<VertexBuffer> vertexBuffer =
        createVertexBuffer(BufferHint::StaticDraw, mesh.vertexCount() * mesh.vertexSize());
    vertexBuffer->bind();
    vertexBuffer->upload(mesh.vertexData());

    // Set up the VertexAttributes
    for (auto &attribute : mesh.vertexAttributes()) {
        VertexBufferAttribute::Type type = [&]() {
            switch (attribute.type()) {
                case VertexAttributeType::Float:
                    return VertexBufferAttribute::Type::Float;
                case VertexAttributeType::UnsignedByte:
                case VertexAttributeType::Double:
                    // TODO: Double precision
                    assert(false);
            }
        }();

        // TODO: Normalize
        vertexArray->add(attribute.name(),
                         {vertexBuffer, type, attribute.components(), false, mesh.vertexSize(), attribute.offset()});
    }

    // Add the indices to the IndexBuffer
    // TODO: support meshes with short indices
    vertexArray->indexBuffer(createIndexBuffer(IndexBufferType::U_INT, BufferHint::StaticDraw, mesh.indexCount()));
    vertexArray->indexBuffer()->bind();
    vertexArray->indexBuffer()->upload(mesh.indexData());

    return vertexArray;
}
void Context::viewport(int width, int height) {
    if (_onResizeListener) {
        (*_onResizeListener)(width, height);
    }
}

}  // namespace renderer
}  // namespace glbr
