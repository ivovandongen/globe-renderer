#pragma once

namespace glbr {
namespace renderer {

enum class DepthTestFunction {
    NEVER,
    LESS,
    EQUAL,
    LESSTHAN_OR_EQUAL,
    GREATER,
    NOT_EQUAL,
    GREATERTHAN_OR_EQUAL,
    ALWAYS
};

struct DepthTest {
    bool enabled{false};
    DepthTestFunction function{DepthTestFunction::LESS};
};

}  // namespace renderer
}  // namespace glbr