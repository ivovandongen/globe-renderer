#pragma once

#include <glbr/renderer/render_state.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

inline GLenum toPolygonMode(RasterizationMode mode) {
    switch (mode) {
        case RasterizationMode::Point:
            return GL_POINT;
        case RasterizationMode::Line:
            return GL_LINE;
        case RasterizationMode::Fill:
            return GL_FILL;
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr