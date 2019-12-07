#pragma once

#include <glbr/core/events/event.hpp>
#include <glbr/core/size.hpp>

namespace glbr {
namespace renderer {

class WindowResizedEvent : public core::EventImpl<WindowResizedEvent> {
public:
    explicit WindowResizedEvent(core::Size2D<int> size) : size_(size) {}

    core::Size2D<int> size() const { return size_; }

    std::string str() const override;

private:
    core::Size2D<int> size_;
};

}  // namespace renderer
}  // namespace glbr
