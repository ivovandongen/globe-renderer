#pragma once

#include <glbr/renderer/clear_state.hpp>
#include <glbr/renderer/render_state.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class RenderStateOpenGL3 {
public:
    RenderStateOpenGL3() = default;

    RenderStateOpenGL3& operator=(const RenderState& update);

    RenderStateOpenGL3& operator=(const ClearState& update);

private:
    RenderState _renderState;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
