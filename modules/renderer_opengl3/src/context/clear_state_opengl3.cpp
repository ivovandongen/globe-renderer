#include <glbr/renderer/opengl3/context/clear_state_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>

#include "shared_state_updates.hpp"

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

ClearStateOpenGL3& ClearStateOpenGL3::operator=(const ClearState& update) {
    // Clear color
    if (update.color != clearState_.color) {
        GL_VERIFY(glClearColor(update.color[0], update.color[1], update.color[2], update.color[3]));
    }

    apply(clearState_.scissorTest, update.scissorTest);
    apply(clearState_.blending, update.blending);

    clearState_ = update;

    return *this;
}

ClearStateOpenGL3& ClearStateOpenGL3::operator=(const RenderState& update) {
    clearState_.scissorTest = update.scissorTest;
    clearState_.blending = update.blending;

    return *this;
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
