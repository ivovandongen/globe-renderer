#pragma once

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

}  // namespace geometry
}  // namespace core
}  // namespace glbr
