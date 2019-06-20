#pragma once

#include <glbr/core/color.hpp>

namespace glbr {
namespace renderer {

enum class SourceBlendingFactor {
    ZERO,
    ONE,
    SOURCE_ALPHA,
    ONE_MINUS_SOURCE_ALPHA,
    DESTINATION_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA,
    DESTINATION_COLOR,
    ONE_MINUS_DESTINATION_COLOR,
    SOURCE_ALPHA_SATURATE,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA
};

enum class DestinationBlendingFactor {
    ZERO,
    ONE,
    SOURCE_COLOR,
    ONE_MINUS_SOURCE_COLOR,
    SOURCE_ALPHA,
    ONE_MINUS_SOURCE_ALPHA,
    DESTINATION_ALPHA,
    ONE_MINUS_DESTINATION_ALPHA,
    DESTINATION_COLOR,
    ONE_MINUS_DESTINATION_COLOR,
    CONSTANT_COLOR,
    ONE_MINUS_CONSTANT_COLOR,
    CONSTANT_ALPHA,
    ONE_MINUS_CONSTANT_ALPHA
};

enum class BlendEquation { ADD, MINIMUM, MAXIMUM, SUBTRACT, REVERSE_SUBTRACT };

struct Blending {
    bool enabled = false;
    SourceBlendingFactor sourceRGBFactor{SourceBlendingFactor::ONE};
    SourceBlendingFactor sourceAlphaFactor{SourceBlendingFactor::ONE};
    DestinationBlendingFactor destinationRGBFactor{DestinationBlendingFactor::ZERO};
    DestinationBlendingFactor destinationAlphaFactor{DestinationBlendingFactor::ZERO};
    BlendEquation rgbEquation{BlendEquation::ADD};
    BlendEquation alphaEquation{BlendEquation::ADD};
    core::Color color{0, 0, 0, 0};

    void factor(SourceBlendingFactor factor) {
        sourceRGBFactor = factor;
        sourceAlphaFactor = factor;
    }

    void factor(DestinationBlendingFactor factor) {
        destinationRGBFactor = factor;
        destinationAlphaFactor = factor;
    }

    void equation(BlendEquation eq) {
        rgbEquation = eq;
        alphaEquation = eq;
    }
};

}  // namespace renderer
}  // namespace glbr