#pragma once

#include <glbr/core/color.hpp>
#include <glbr/renderer/state/blending.hpp>
#include <glbr/renderer/state/clear_buffers.hpp>
#include <glbr/renderer/state/scissor_test.hpp>

namespace glbr {
namespace renderer {

struct ClearState {
    ClearBuffers buffers;
    core::Color color;
    ScissorTest scissorTest;
    Blending blending;
};

}  // namespace renderer
}  // namespace glbr