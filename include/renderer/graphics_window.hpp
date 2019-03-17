#pragma once

namespace renderer {

enum class WindowType {
    Default = 0,
    FullScreen = 1
};

class GraphicsWindow {
public:
    virtual ~GraphicsWindow() = default;

    virtual void makeContextCurrent() const = 0;

    virtual void run() = 0;
};

} // namespace renderer