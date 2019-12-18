#pragma once

#include <glbr/core/events/event.hpp>

namespace glbr {
namespace input {

class MouseMoveEvent : public core::EventImpl<MouseMoveEvent> {
public:
    MouseMoveEvent(double x, double y) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }

    std::string str() const override;

private:
    double x_;
    double y_;
};

}  // namespace input
}  // namespace glbr