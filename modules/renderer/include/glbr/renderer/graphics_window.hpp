#pragma once

#include <functional>

namespace glbr {
namespace renderer {

enum class WindowType { Default = 0, FullScreen = 1 };

class GraphicsWindow {
public:
    virtual ~GraphicsWindow() = default;

    virtual void makeContextCurrent() const = 0;

    virtual Context &context() const = 0;

    virtual void run(const std::function<void(Context &)> &onRenderFrame) = 0;

    virtual void run(const std::function<void(Context &)> &onRenderFrame, const std::function<void()> &onUpdateFrame,
                     double updateRate) = 0;
};

}  // namespace renderer
}  // namespace glbr