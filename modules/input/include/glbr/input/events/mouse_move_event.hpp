#pragma once

#include <glbr/core/events/event.hpp>

namespace glbr {
namespace input {

class MouseMoveEvent : public core::EventImpl<MouseMoveEvent> {
public:
    MouseMoveEvent(double x, double y) : _x(x), _y(y) {}

    double x() const { return _x; }
    double y() const { return _y; }

    std::string str() override;

private:
    double _x;
    double _y;
};

}  // namespace input
}  // namespace glbr