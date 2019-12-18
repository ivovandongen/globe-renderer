#pragma once

#include <glbr/core/events/event.hpp>

namespace glbr {
namespace input {

class MouseScrollEvent : public core::EventImpl<MouseScrollEvent> {
public:
    MouseScrollEvent(double offsetX, double offsetY) : offsetX_(offsetX), offsetY_(offsetY) {}

    double offsetX() const { return offsetX_; }
    double offsetY() const { return offsetY_; }

    std::string str() const override;

private:
    double offsetX_;
    double offsetY_;
};

}  // namespace input
}  // namespace glbr