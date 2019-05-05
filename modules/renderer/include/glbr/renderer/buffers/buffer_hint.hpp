#pragma once

namespace glbr {
namespace renderer {

enum class BufferHint {
    StreamDraw,
    StreamRead,
    StreamCopy,
    StaticDraw,
    StaticRead,
    StaticCopy,
    DynamicDraw,
    DynamicRead,
    DynamicCopy,
};

}  // namespace renderer
}  // namespace glbr