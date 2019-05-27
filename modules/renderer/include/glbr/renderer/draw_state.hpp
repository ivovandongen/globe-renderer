#pragma once

#include <glbr/renderer/pipeline.hpp>
#include <glbr/renderer/render_state.hpp>
#include <glbr/renderer/vertex_array/vertex_array.hpp>

namespace glbr {
namespace renderer {

struct DrawState {
    RenderState renderState;
    std::shared_ptr<Pipeline> pipeline;
    std::shared_ptr<VertexArray> vertexArray;
};

}  // namespace renderer
}  // namespace glbr