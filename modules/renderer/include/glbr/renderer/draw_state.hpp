#pragma once

#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/render_state.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

namespace glbr {
namespace renderer {

struct DrawState {
    RenderState renderState;
    Pipeline &pipeline;
    VertexArray &vertexArray;
};

}  // namespace renderer
}  // namespace glbr