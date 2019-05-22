#pragma once

#include "vertex_attributes/vertex_attribute.hpp"

#include <cassert>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

namespace glbr {
namespace core {
namespace geometry {

enum class PrimitiveType {
    Points,
    Lines,
    LineLoop,
    LineStrip,
    Triangles,
    TriangleStrip,
    TriangleFan,
    LinesAdjacency,
    LineStripAdjacency,
    TrianglesAdjacency,
    TriangleStripAdjacency
};

enum class WindingOrder { Clockwise, Counterclockwise };

template <class Vertex, class Index>
class MeshImpl;

class Mesh {
public:
    using VertexAttributes = std::vector<VertexAttribute>;

    virtual ~Mesh() = default;

    virtual const VertexAttributes& vertexAttributes() const = 0;

    virtual const void* vertexData() const = 0;
    virtual const size_t vertexCount() const = 0;
    virtual const unsigned int vertexSize() const = 0;

    virtual const void* indexData() const = 0;
    virtual const size_t indexCount() const = 0;
    virtual const unsigned int indexSize() const = 0;

    template <class Vertex, class Index>
    static std::unique_ptr<MeshImpl<Vertex, Index>> Create(std::initializer_list<VertexAttribute> attributes,
                                                           PrimitiveType primitiveType = PrimitiveType::Triangles,
                                                           WindingOrder windingOrder = WindingOrder::Counterclockwise) {
        return std::make_unique<MeshImpl<Vertex, Index>>(attributes, primitiveType, windingOrder);
    }
};

template <class Vertex, class Index>
class MeshImpl : public Mesh {
public:
    MeshImpl(std::initializer_list<VertexAttribute> attributes, PrimitiveType primitiveType, WindingOrder windingOrder)
        : _primitiveType(primitiveType), _windingOrder(windingOrder), _vertexAttributes(attributes) {
        // Check that the defined attribute bindings size does not exceed  the vertex size
        assert(sizeof(Vertex) >= std::prev(attributes.end())->offset() + std::prev(attributes.end())->size());
    }

    ~MeshImpl() override = default;

    const VertexAttributes& vertexAttributes() const override { return _vertexAttributes; }

    inline const PrimitiveType& primitiveType() const { return _primitiveType; }
    inline const WindingOrder& windingOrder() const { return _windingOrder; }

    void data(std::vector<Vertex>&& data) { _data = std::move(data); }
    void indices(std::vector<Index>&& indices) { _indices = std::move(indices); };

    // MeshBase implementation

    inline const void* vertexData() const override { return _data.data(); }
    inline const size_t vertexCount() const override { return _data.size(); }
    inline const unsigned int vertexSize() const override { return sizeof(Vertex); }

    inline const void* indexData() const override { return _indices.data(); }
    inline const size_t indexCount() const override { return _indices.size(); }
    inline const unsigned int indexSize() const override { return sizeof(Index); }

private:
    PrimitiveType _primitiveType;
    WindingOrder _windingOrder;
    VertexAttributes _vertexAttributes;
    std::vector<Vertex> _data;
    std::vector<Index> _indices;
};

}  // namespace geometry
}  // namespace core
}  // namespace glbr
