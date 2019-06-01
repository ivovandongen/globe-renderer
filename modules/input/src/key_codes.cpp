#include <glbr/input/key_codes.hpp>

namespace glbr {
namespace input {

std::ostream& operator<<(std::ostream& os, const KeyCode& code) {
    switch (code) {
        case KeyCode::KEY_UNKNOWN:
            os << "KEY_UNKNOWN";
            break;
        case KeyCode::KEY_SPACE:
            os << "KEY_SPACE";
            break;
        case KeyCode::KEY_APOSTROPHE:
            os << "KEY_APOSTROPHE";
            break;
        case KeyCode::KEY_COMMA:
            os << "KEY_COMMA";
            break;
        case KeyCode::KEY_MINUS:
            os << "KEY_MINUS";
            break;
        case KeyCode::KEY_PERIOD:
            os << "KEY_PERIOD";
            break;
        case KeyCode::KEY_SLASH:
            os << "KEY_SLASH";
            break;
        case KeyCode::KEY_0:
            os << "KEY_0";
            break;
        case KeyCode::KEY_1:
            os << "KEY_1";
            break;
        case KeyCode::KEY_2:
            os << "KEY_2";
            break;
        case KeyCode::KEY_3:
            os << "KEY_3";
            break;
        case KeyCode::KEY_4:
            os << "KEY_4";
            break;
        case KeyCode::KEY_5:
            os << "KEY_5";
            break;
        case KeyCode::KEY_6:
            os << "KEY_6";
            break;
        case KeyCode::KEY_7:
            os << "KEY_7";
            break;
        case KeyCode::KEY_8:
            os << "KEY_8";
            break;
        case KeyCode::KEY_9:
            os << "KEY_9";
            break;
        case KeyCode::KEY_SEMICOLON:
            os << "KEY_SEMICOLON";
            break;
        case KeyCode::KEY_EQUAL:
            os << "KEY_EQUAL";
            break;
        case KeyCode::KEY_A:
            os << "KEY_A";
            break;
        case KeyCode::KEY_B:
            os << "KEY_B";
            break;
        case KeyCode::KEY_C:
            os << "KEY_C";
            break;
        case KeyCode::KEY_D:
            os << "KEY_D";
            break;
        case KeyCode::KEY_E:
            os << "KEY_E";
            break;
        case KeyCode::KEY_F:
            os << "KEY_F";
            break;
        case KeyCode::KEY_G:
            os << "KEY_G";
            break;
        case KeyCode::KEY_H:
            os << "KEY_H";
            break;
        case KeyCode::KEY_I:
            os << "KEY_I";
            break;
        case KeyCode::KEY_J:
            os << "KEY_J";
            break;
        case KeyCode::KEY_K:
            os << "KEY_K";
            break;
        case KeyCode::KEY_L:
            os << "KEY_L";
            break;
        case KeyCode::KEY_M:
            os << "KEY_M";
            break;
        case KeyCode::KEY_N:
            os << "KEY_N";
            break;
        case KeyCode::KEY_O:
            os << "KEY_O";
            break;
        case KeyCode::KEY_P:
            os << "KEY_P";
            break;
        case KeyCode::KEY_Q:
            os << "KEY_Q";
            break;
        case KeyCode::KEY_R:
            os << "KEY_R";
            break;
        case KeyCode::KEY_S:
            os << "KEY_S";
            break;
        case KeyCode::KEY_T:
            os << "KEY_T";
            break;
        case KeyCode::KEY_U:
            os << "KEY_U";
            break;
        case KeyCode::KEY_V:
            os << "KEY_V";
            break;
        case KeyCode::KEY_W:
            os << "KEY_W";
            break;
        case KeyCode::KEY_X:
            os << "KEY_X";
            break;
        case KeyCode::KEY_Y:
            os << "KEY_Y";
            break;
        case KeyCode::KEY_Z:
            os << "KEY_Z";
            break;
        case KeyCode::KEY_LEFT_BRACKET:
            os << "KEY_LEFT_BRACKET";
            break;
        case KeyCode::KEY_BACKSLASH:
            os << "KEY_BACKSLASH";
            break;
        case KeyCode::KEY_RIGHT_BRACKET:
            os << "KEY_RIGHT_BRACKET";
            break;
        case KeyCode::KEY_GRAVE_ACCENT:
            os << "KEY_GRAVE_ACCENT";
            break;
        case KeyCode::KEY_WORLD_1:
            os << "KEY_WORLD_1";
            break;
        case KeyCode::KEY_WORLD_2:
            os << "KEY_WORLD_2";
            break;
        case KeyCode::KEY_ESCAPE:
            os << "KEY_ESCAPE";
            break;
        case KeyCode::KEY_ENTER:
            os << "KEY_ENTER";
            break;
        case KeyCode::KEY_TAB:
            os << "KEY_TAB";
            break;
        case KeyCode::KEY_BACKSPACE:
            os << "KEY_BACKSPACE";
            break;
        case KeyCode::KEY_INSERT:
            os << "KEY_INSERT";
            break;
        case KeyCode::KEY_DELETE:
            os << "KEY_DELETE";
            break;
        case KeyCode::KEY_RIGHT:
            os << "KEY_RIGHT";
            break;
        case KeyCode::KEY_LEFT:
            os << "KEY_LEFT";
            break;
        case KeyCode::KEY_DOWN:
            os << "KEY_DOWN";
            break;
        case KeyCode::KEY_UP:
            os << "KEY_UP";
            break;
        case KeyCode::KEY_PAGE_UP:
            os << "KEY_PAGE_UP";
            break;
        case KeyCode::KEY_PAGE_DOWN:
            os << "KEY_PAGE_DOWN";
            break;
        case KeyCode::KEY_HOME:
            os << "KEY_HOME";
            break;
        case KeyCode::KEY_END:
            os << "KEY_END";
            break;
        case KeyCode::KEY_CAPS_LOCK:
            os << "KEY_CAPS_LOCK";
            break;
        case KeyCode::KEY_SCROLL_LOCK:
            os << "KEY_SCROLL_LOCK";
            break;
        case KeyCode::KEY_NUM_LOCK:
            os << "KEY_NUM_LOCK";
            break;
        case KeyCode::KEY_PRINT_SCREEN:
            os << "KEY_PRINT_SCREEN";
            break;
        case KeyCode::KEY_PAUSE:
            os << "KEY_PAUSE";
            break;
        case KeyCode::KEY_F1:
            os << "KEY_F1";
            break;
        case KeyCode::KEY_F2:
            os << "KEY_F2";
            break;
        case KeyCode::KEY_F3:
            os << "KEY_F3";
            break;
        case KeyCode::KEY_F4:
            os << "KEY_F4";
            break;
        case KeyCode::KEY_F5:
            os << "KEY_F5";
            break;
        case KeyCode::KEY_F6:
            os << "KEY_F6";
            break;
        case KeyCode::KEY_F7:
            os << "KEY_F7";
            break;
        case KeyCode::KEY_F8:
            os << "KEY_F8";
            break;
        case KeyCode::KEY_F9:
            os << "KEY_F9";
            break;
        case KeyCode::KEY_F10:
            os << "KEY_F10";
            break;
        case KeyCode::KEY_F11:
            os << "KEY_F11";
            break;
        case KeyCode::KEY_F12:
            os << "KEY_F12";
            break;
        case KeyCode::KEY_F13:
            os << "KEY_F13";
            break;
        case KeyCode::KEY_F14:
            os << "KEY_F14";
            break;
        case KeyCode::KEY_F15:
            os << "KEY_F15";
            break;
        case KeyCode::KEY_F16:
            os << "KEY_F16";
            break;
        case KeyCode::KEY_F17:
            os << "KEY_F17";
            break;
        case KeyCode::KEY_F18:
            os << "KEY_F18";
            break;
        case KeyCode::KEY_F19:
            os << "KEY_F19";
            break;
        case KeyCode::KEY_F20:
            os << "KEY_F20";
            break;
        case KeyCode::KEY_F21:
            os << "KEY_F21";
            break;
        case KeyCode::KEY_F22:
            os << "KEY_F22";
            break;
        case KeyCode::KEY_F23:
            os << "KEY_F23";
            break;
        case KeyCode::KEY_F24:
            os << "KEY_F24";
            break;
        case KeyCode::KEY_F25:
            os << "KEY_F25";
            break;
        case KeyCode::KEY_KP_0:
            os << "KEY_KP_0";
            break;
        case KeyCode::KEY_KP_1:
            os << "KEY_KP_1";
            break;
        case KeyCode::KEY_KP_2:
            os << "KEY_KP_2";
            break;
        case KeyCode::KEY_KP_3:
            os << "KEY_KP_3";
            break;
        case KeyCode::KEY_KP_4:
            os << "KEY_KP_4";
            break;
        case KeyCode::KEY_KP_5:
            os << "KEY_KP_5";
            break;
        case KeyCode::KEY_KP_6:
            os << "KEY_KP_6";
            break;
        case KeyCode::KEY_KP_7:
            os << "KEY_KP_7";
            break;
        case KeyCode::KEY_KP_8:
            os << "KEY_KP_8";
            break;
        case KeyCode::KEY_KP_9:
            os << "KEY_KP_9";
            break;
        case KeyCode::KEY_KP_DECIMAL:
            os << "KEY_KP_DECIMAL";
            break;
        case KeyCode::KEY_KP_DIVIDE:
            os << "KEY_KP_DIVIDE";
            break;
        case KeyCode::KEY_KP_MULTIPLY:
            os << "KEY_KP_MULTIPLY";
            break;
        case KeyCode::KEY_KP_SUBTRACT:
            os << "KEY_KP_SUBTRACT";
            break;
        case KeyCode::KEY_KP_ADD:
            os << "KEY_KP_ADD";
            break;
        case KeyCode::KEY_KP_ENTER:
            os << "KEY_KP_ENTER";
            break;
        case KeyCode::KEY_KP_EQUAL:
            os << "KEY_KP_EQUAL";
            break;
        case KeyCode::KEY_LEFT_SHIFT:
            os << "KEY_LEFT_SHIFT";
            break;
        case KeyCode::KEY_LEFT_CONTROL:
            os << "KEY_LEFT_CONTROL";
            break;
        case KeyCode::KEY_LEFT_ALT:
            os << "KEY_LEFT_ALT";
            break;
        case KeyCode::KEY_LEFT_SUPER:
            os << "KEY_LEFT_SUPER";
            break;
        case KeyCode::KEY_RIGHT_SHIFT:
            os << "KEY_RIGHT_SHIFT";
            break;
        case KeyCode::KEY_RIGHT_CONTROL:
            os << "KEY_RIGHT_CONTROL";
            break;
        case KeyCode::KEY_RIGHT_ALT:
            os << "KEY_RIGHT_ALT";
            break;
        case KeyCode::KEY_RIGHT_SUPER:
            os << "KEY_RIGHT_SUPER";
            break;
        case KeyCode::KEY_MENU:
            os << "KEY_MENU";
            break;
    }
    return os;
}
}  // namespace input
}  // namespace glbr