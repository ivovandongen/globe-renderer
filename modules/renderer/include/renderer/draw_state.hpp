#pragma once

#include <renderer/render_state.hpp>
#include <renderer/pipeline.hpp>
#include <renderer/vertex_array/vertex_array.hpp>

namespace renderer {

struct DrawState {
    RenderState renderState;
    Pipeline &pipeline;
    VertexArray &vertexArray;
};

} // namespace renderer