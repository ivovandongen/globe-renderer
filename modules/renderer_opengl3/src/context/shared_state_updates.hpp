#pragma once

#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/type_conversions_opengl3.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

inline void enable(GLenum capability, bool enable) {
    if (enable) {
        GL_VERIFY(glEnable(capability));
    } else {
        GL_VERIFY(glDisable(capability));
    }
}

inline void apply(const ScissorTest& current, const ScissorTest& update) {
    if (update.enabled != current.enabled) {
        enable(GL_SCISSOR_TEST, update.enabled);
    }

    // TODO apply only when enabled
    if (update.rectangle != current.rectangle) {
        auto& rect = update.rectangle;
        GL_VERIFY(glScissor(rect.x, rect.y, rect.width, rect.height));
    }
};

inline void apply(const Blending& current, const Blending& update) {
    if (update.enabled != current.enabled) {
        enable(GL_BLEND, update.enabled);
    }

    // TODO apply only when enabled
    if ((current.sourceRGBFactor != update.sourceRGBFactor) ||
        (current.destinationRGBFactor != update.destinationRGBFactor) ||
        (current.sourceAlphaFactor != update.sourceAlphaFactor) ||
        (current.destinationAlphaFactor != update.destinationAlphaFactor)) {
        GL_VERIFY(glBlendFuncSeparate(toSourceBlendingFactor(update.sourceRGBFactor),
                                      toDestinationBlendingFactor(update.destinationRGBFactor),
                                      toSourceBlendingFactor(update.sourceAlphaFactor),
                                      toDestinationBlendingFactor(update.destinationAlphaFactor)));
    }

    if ((current.rgbEquation != update.rgbEquation) || (current.alphaEquation != update.alphaEquation)) {
        GL_VERIFY(glBlendEquationSeparate(toBlendEquationMode(update.rgbEquation),
                                          toBlendEquationMode(update.alphaEquation)));
    }

    if (current.color != update.color) {
        GL_VERIFY(glBlendColor(update.color.r, update.color.g, update.color.b, update.color.a));
    }
}

inline void apply(const DepthTest& current, const DepthTest& update) {
    if (update.enabled != current.enabled) {
        enable(GL_DEPTH, update.enabled);
    }

    // TODO apply only when enabled
    if (update.function != current.function) {
        GL_VERIFY(glDepthFunc(toDepthFunction(update.function)));
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr