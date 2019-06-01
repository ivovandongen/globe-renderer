#include <glbr/input/events/mouse_move_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string MouseMoveEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[x:" << _x << ", y:" << _y << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr