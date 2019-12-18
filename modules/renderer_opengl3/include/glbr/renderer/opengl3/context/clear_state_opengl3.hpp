#pragma once

#include <glbr/renderer/clear_state.hpp>
#include <glbr/renderer/render_state.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ClearStateOpenGL3 {
public:
    ClearStateOpenGL3() = default;

    ClearStateOpenGL3& operator=(const ClearState& update);

    ClearStateOpenGL3& operator=(const RenderState& update);

private:
    ClearState clearState_;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
