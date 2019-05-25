#pragma once

#include <functional>

namespace glbr {
namespace renderer {

enum class WindowType { Default = 0, FullScreen = 1 };

class GraphicsWindow {
public:
    using RenderFN = std::function<void(Context &)>;
    using UpdateFN = std::function<void()>;

    virtual ~GraphicsWindow() = default;

    virtual void makeContextCurrent() const = 0;

    virtual Context &context() const = 0;

    virtual void run(const RenderFN &onRenderFrame) = 0;

    virtual void run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) = 0;
};

}  // namespace renderer
}  // namespace glbr