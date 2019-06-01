#pragma once

#include <ostream>

namespace glbr {
namespace input {

enum class MouseButtonCode : int8_t {
    MOUSE_BUTTON_1 = 0,
    MOUSE_BUTTON_2 = 1,
    MOUSE_BUTTON_3 = 2,
    MOUSE_BUTTON_4 = 3,
    MOUSE_BUTTON_5 = 4,
    MOUSE_BUTTON_6 = 5,
    MOUSE_BUTTON_7 = 6,
    MOUSE_BUTTON_8 = 7

};

std::ostream &operator<<(std::ostream &os, const MouseButtonCode &code);

}  // namespace input
}  // namespace glbr