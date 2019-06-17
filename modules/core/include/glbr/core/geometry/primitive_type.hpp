#pragma once

namespace glbr {
namespace core {
namespace geometry {

enum class PrimitiveType {
    POINTS,
    LINES,
    LINE_LOOP,
    LINE_STRIP,
    TRIANGLES,
    TRIANGLE_STRIP,
    TRIANGLE_FAN,
    LINES_ADJACENCY,
    LINE_STRIP_ADJACENCY,
    TRIANGLES_ADJACENCY,
    TRIANGLE_STRIP_ADJACENCY
};

}  // namespace geometry
}  // namespace core
}  // namespace glbr
