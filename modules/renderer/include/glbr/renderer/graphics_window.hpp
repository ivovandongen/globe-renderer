#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/core/events/event_producer.hpp>
#include <glbr/core/size.hpp>
#include <glbr/input/input.hpp>
#include <glbr/renderer/context.hpp>

#include <chrono>
#include <functional>

namespace glbr {
namespace renderer {

enum class WindowType { Default = 0, FullScreen = 1 };

class GraphicsWindow : public input::Input, public core::EventProducer {
public:
    using RenderFN = std::function<void(Context &)>;
    using UpdateFN = std::function<void(std::chrono::nanoseconds)>;

    ~GraphicsWindow() override = default;

    virtual void makeContextCurrent() const = 0;

    virtual Context &context() const = 0;

    virtual core::Size2D<int> size() const = 0;

    virtual float pixelRatio() const = 0;

    virtual void run(const RenderFN &onRenderFrame) = 0;

    virtual void run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) = 0;

    virtual void close() = 0;
};

}  // namespace renderer
}  // namespace glbr