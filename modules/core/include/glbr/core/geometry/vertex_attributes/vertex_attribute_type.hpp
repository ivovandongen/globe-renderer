#pragma once

namespace glbr {
namespace core {
namespace geometry {

enum class VertexAttributeType { UnsignedByte, Float, Double };

inline int sizeOf(VertexAttributeType type) {
    switch (type) {
        case VertexAttributeType::UnsignedByte:
            return sizeof(unsigned char);
        case VertexAttributeType::Float:
            return sizeof(float);
        case VertexAttributeType::Double:
            return sizeof(double);
    }
}

}  // namespace geometry
}  // namespace core
}  // namespace glbr