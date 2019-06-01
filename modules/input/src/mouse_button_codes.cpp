#include <glbr/input/mouse_button_codes.hpp>

namespace glbr {
namespace input {

std::ostream& operator<<(std::ostream& os, const MouseButtonCode& code) {
    switch (code) {
        case MouseButtonCode::MOUSE_BUTTON_1:
            os << "BUTTON_1";
            break;
        case MouseButtonCode::MOUSE_BUTTON_2:
            os << "BUTTON_2";
            break;
        case MouseButtonCode::MOUSE_BUTTON_3:
            os << "BUTTON_3";
            break;
        case MouseButtonCode::MOUSE_BUTTON_4:
            os << "BUTTON_4";
            break;
        case MouseButtonCode::MOUSE_BUTTON_5:
            os << "BUTTON_5";
            break;
        case MouseButtonCode::MOUSE_BUTTON_6:
            os << "BUTTON_6";
            break;
        case MouseButtonCode::MOUSE_BUTTON_7:
            os << "BUTTON_7";
            break;
        case MouseButtonCode::MOUSE_BUTTON_8:
            os << "BUTTON_8";
            break;
        default:
            os << "UNKNOWN";
            break;
    }
    return os;
}
}  // namespace input
}  // namespace glbr