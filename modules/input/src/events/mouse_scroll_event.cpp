#include <glbr/input/events/mouse_scroll_event.hpp>

#include <sstream>

namespace glbr {
namespace input {

std::string MouseScrollEvent::str() const {
    std::stringstream ss;
    ss << EventImpl::str() << "[offset x:" << offsetX_ << ", offset y:" << offsetY_ << "]";
    return ss.str();
}

}  // namespace input
}  // namespace glbr