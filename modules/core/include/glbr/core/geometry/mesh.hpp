#pragma once

#include "primitive_type.hpp"
#include "vertex_attributes/vertex_attribute.hpp"
#include "winding_order.hpp"

#include <cassert>
#include <memory>
#include <numeric>
#include <string>
#include <unordered_map>
#include <vector>

namespace glbr {
namespace core {
namespace geometry {

template <class Vertex, class Index>
class MeshImpl;

class Mesh {
public:
    using VertexAttributes = std::vector<VertexAttribute>;

    Mesh(PrimitiveType primitiveType, WindingOrder windingOrder)
        : primitiveType_(primitiveType), windingOrder_(windingOrder) {}
    virtual ~Mesh() = default;

    inline const PrimitiveType& primitiveType() const { return primitiveType_; }
    inline const WindingOrder& windingOrder() const { return windingOrder_; }

    virtual const VertexAttributes& vertexAttributes() const = 0;

    virtual const void* vertexData() const = 0;
    virtual const size_t vertexCount() const = 0;
    virtual const unsigned int vertexSize() const = 0;

    virtual const void* indexData() const = 0;
    virtual const size_t indexCount() const = 0;

    template <class Vertex, class Index>
    static std::unique_ptr<MeshImpl<Vertex, Index>> Create(
        std::initializer_list<VertexAttribute> attributes,
        PrimitiveType primitiveType = PrimitiveType::TRIANGLES,
        WindingOrder windingOrder = WindingOrder::COUNTER_CLOCK_WISE) {
        return std::make_unique<MeshImpl<Vertex, Index>>(attributes, primitiveType, windingOrder);
    }

private:
    PrimitiveType primitiveType_;
    WindingOrder windingOrder_;
};

template <class Vertex, class Index>
class MeshImpl : public Mesh {
public:
    MeshImpl(std::initializer_list<VertexAttribute> attributes, PrimitiveType primitiveType, WindingOrder windingOrder)
        : Mesh(primitiveType, windingOrder), vertexAttributes_(attributes) {
        // Check that the defined attribute bindings size does not exceed  the vertex size
        assert(sizeof(Vertex) >= std::prev(attributes.end())->offset() + std::prev(attributes.end())->size());
    }

    ~MeshImpl() override = default;

    const VertexAttributes& vertexAttributes() const override { return vertexAttributes_; }

    void data(std::vector<Vertex>&& data) { data_ = std::move(data); }
    void indices(std::vector<Index>&& indices) { indices_ = std::move(indices); };

    // MeshBase implementation

    inline const void* vertexData() const override { return data_.data(); }
    inline const size_t vertexCount() const override { return data_.size(); }
    inline const unsigned int vertexSize() const override { return sizeof(Vertex); }

    inline const void* indexData() const override { return indices_.data(); }
    inline const size_t indexCount() const override { return indices_.size() * sizeof(Index) / sizeof(uint32_t); }

private:
    VertexAttributes vertexAttributes_;
    std::vector<Vertex> data_;
    std::vector<Index> indices_;
};

}  // namespace geometry
}  // namespace core
}  // namespace glbr
