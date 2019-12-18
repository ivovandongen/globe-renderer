#include <glbr/renderer/opengl3/context/render_state_opengl3.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

#include "shared_state_updates.hpp"

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

RenderStateOpenGL3& RenderStateOpenGL3::operator=(const RenderState& update) {
    if (renderState_.rasterizationMode != update.rasterizationMode) {
        GL_VERIFY(glPolygonMode(GL_FRONT_AND_BACK, toPolygonMode(update.rasterizationMode)));
    }

    if (renderState_.faceCulling != update.faceCulling) {
        GL_VERIFY(update.faceCulling.enabled ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE));
        GL_VERIFY(glCullFace(toCullFace(update.faceCulling.cullFace)));
        GL_VERIFY(glFrontFace(toWindingOrder(update.faceCulling.frontFaceWindingOrder)));
    }

    apply(renderState_.scissorTest, update.scissorTest);
    apply(renderState_.blending, update.blending);
    apply(renderState_.depthTest, update.depthTest);

    renderState_ = update;

    return *this;
}

RenderStateOpenGL3& RenderStateOpenGL3::operator=(const ClearState& update) {
    renderState_.scissorTest = update.scissorTest;
    renderState_.blending = update.blending;

    return *this;
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
