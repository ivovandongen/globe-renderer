#include <glbr/input/events/mouse_scroll_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string MouseScrollEvent::str() {
    std::stringstream ss;
    ss << EventImpl::str() << "[offset x:" << _offsetX << ", offset y:" << _offsetY << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr