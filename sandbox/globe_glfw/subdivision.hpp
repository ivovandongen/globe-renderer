#pragma once

#include <glbr/core/geometry/mesh.hpp>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <cmath>
#include <vector>

namespace {

int indexCount(int subdivisions) {
    int triangles = 0;
    for (int i = 0; i <= subdivisions; ++i) {
        triangles += int(pow(4, i));
    }
    triangles *= 4;
    return triangles;
}

int vertexCount(int subdivisions) {
    int vertices = 0;
    for (int i = 0; i < subdivisions; ++i) {
        vertices += int(pow(4, i));
    }
    vertices = 4 + (12 * vertices);

    return vertices;
}

template <class Vertex, class Index>
void subdivide(std::vector<Vertex>& vertices, std::vector<Index>& indices, Index triangle, int level) {
    if (level > 0) {
        vertices.push_back(glm::normalize((vertices[triangle[0]] + vertices[triangle[1]]) * 0.5f));
        vertices.push_back(glm::normalize((vertices[triangle[1]] + vertices[triangle[2]]) * 0.5f));
        vertices.push_back(glm::normalize((vertices[triangle[2]] + vertices[triangle[0]]) * 0.5f));

        int i01 = vertices.size() - 3;
        int i12 = vertices.size() - 2;
        int i20 = vertices.size() - 1;

        //
        // Subdivide input triangle into four triangles
        //
        --level;
        subdivide(vertices, indices, {triangle[0], i01, i20}, level);
        subdivide(vertices, indices, {i01, triangle[1], i12}, level);
        subdivide(vertices, indices, {i01, i12, i20}, level);
        subdivide(vertices, indices, {i20, i12, triangle[2]}, level);
    } else {
        indices.push_back(triangle);
    }
}

}  // namespace

std::unique_ptr<glbr::core::geometry::Mesh> subdivision(int subdivisions) {
    using FT = float;
    using namespace glbr::core::geometry;

    using Vertex = glm::vec3;
    using Index = std::array<int, 3>;

    //
    // Initial tetrahedron
    //
    FT negativeRootTwoOverThree = -sqrt(2.0) / 3.0;
    const FT negativeOneThird = -1.0 / 3.0;
    FT rootSixOverThree = sqrt(6.0) / 3.0;

    std::vector<Vertex> vertices;
    vertices.reserve(vertexCount(subdivisions));

    vertices.emplace_back(0, 0, 1);
    vertices.emplace_back(0, FT((2.0 * sqrt(2.0)) / 3.0), negativeOneThird);
    vertices.emplace_back(-rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);
    vertices.emplace_back(rootSixOverThree, negativeRootTwoOverThree, negativeOneThird);

    std::vector<Index> indices;
    indices.reserve(indexCount(subdivisions));

    subdivide(vertices, indices, {0, 1, 2}, subdivisions);
    subdivide(vertices, indices, {0, 2, 3}, subdivisions);
    subdivide(vertices, indices, {0, 3, 1}, subdivisions);
    subdivide(vertices, indices, {1, 3, 2}, subdivisions);

    // Create the mesh

    auto mesh = Mesh::Create<Vertex, Index>({{"position", VertexAttributeType::Float, 3}});

    // Add data
    mesh->data(std::move(vertices));

    // Add indices
    mesh->indices(std::move(indices));

    return mesh;
}