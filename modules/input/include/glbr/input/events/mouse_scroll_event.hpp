#pragma once

#include <glbr/core/events/event.hpp>

namespace glbr {
namespace input {

class MouseScrollEvent : public core::EventImpl<MouseScrollEvent> {
public:
    MouseScrollEvent(double offsetX, double offsetY) : _offsetX(offsetX), _offsetY(offsetY) {}

    double offsetX() const { return _offsetX; }
    double offsetY() const { return _offsetY; }

    std::string str() override;

private:
    double _offsetX;
    double _offsetY;
};

}  // namespace input
}  // namespace glbr