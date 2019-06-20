#include <glbr/renderer/opengl3/context/clear_state_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>
#include "shared_state_updates.hpp"

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

ClearStateOpenGL3& ClearStateOpenGL3::operator=(const ClearState& update) {
    // Clear color
    if (update.color != _clearState.color) {
        GL_VERIFY(glClearColor(update.color[0], update.color[1], update.color[2], update.color[3]));
    }

    apply(_clearState.scissorTest, update.scissorTest);
    apply(_clearState.blending, update.blending);

    _clearState = update;

    return *this;
}

ClearStateOpenGL3& ClearStateOpenGL3::operator=(const RenderState& update) {
    _clearState.scissorTest = update.scissorTest;
    _clearState.blending = update.blending;

    return *this;
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
