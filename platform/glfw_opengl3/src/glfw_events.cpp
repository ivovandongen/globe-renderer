#include "glfw_events.hpp"
#include "glfw_system.hpp"

#include <cassert>

namespace glbr {
namespace renderer {
namespace glfw {

input::KeyEvent::Action convertAction(int action) {
    using namespace input;
    switch (action) {
        case GLFW_PRESS:
            return KeyEvent::Action::PRESS;
        case GLFW_RELEASE:
            return KeyEvent::Action::RELEASE;
        case GLFW_REPEAT:
            return KeyEvent::Action::REPEAT;
        default:
            assert((printf("No action defined for: %i", action), false));
    }
}

input::KeyCode convertKey(int key) {
    using namespace input;

    switch (key) {
        case GLFW_KEY_UNKNOWN:
            return KeyCode::KEY_UNKNOWN;
        case GLFW_KEY_SPACE:
            return KeyCode::KEY_SPACE;
        case GLFW_KEY_APOSTROPHE:
            return KeyCode::KEY_APOSTROPHE;
        case GLFW_KEY_COMMA:
            return KeyCode::KEY_COMMA;
        case GLFW_KEY_MINUS:
            return KeyCode::KEY_MINUS;
        case GLFW_KEY_PERIOD:
            return KeyCode::KEY_PERIOD;
        case GLFW_KEY_SLASH:
            return KeyCode::KEY_SLASH;
        case GLFW_KEY_0:
            return KeyCode::KEY_0;
        case GLFW_KEY_1:
            return KeyCode::KEY_1;
        case GLFW_KEY_2:
            return KeyCode::KEY_2;
        case GLFW_KEY_3:
            return KeyCode::KEY_3;
        case GLFW_KEY_4:
            return KeyCode::KEY_4;
        case GLFW_KEY_5:
            return KeyCode::KEY_5;
        case GLFW_KEY_6:
            return KeyCode::KEY_6;
        case GLFW_KEY_7:
            return KeyCode::KEY_7;
        case GLFW_KEY_8:
            return KeyCode::KEY_8;
        case GLFW_KEY_9:
            return KeyCode::KEY_9;
        case GLFW_KEY_SEMICOLON:
            return KeyCode::KEY_SEMICOLON;
        case GLFW_KEY_EQUAL:
            return KeyCode::KEY_EQUAL;
        case GLFW_KEY_A:
            return KeyCode::KEY_A;
        case GLFW_KEY_B:
            return KeyCode::KEY_B;
        case GLFW_KEY_C:
            return KeyCode::KEY_C;
        case GLFW_KEY_D:
            return KeyCode::KEY_D;
        case GLFW_KEY_E:
            return KeyCode::KEY_E;
        case GLFW_KEY_F:
            return KeyCode::KEY_F;
        case GLFW_KEY_G:
            return KeyCode::KEY_G;
        case GLFW_KEY_H:
            return KeyCode::KEY_H;
        case GLFW_KEY_I:
            return KeyCode::KEY_I;
        case GLFW_KEY_J:
            return KeyCode::KEY_J;
        case GLFW_KEY_K:
            return KeyCode::KEY_K;
        case GLFW_KEY_L:
            return KeyCode::KEY_L;
        case GLFW_KEY_M:
            return KeyCode::KEY_M;
        case GLFW_KEY_N:
            return KeyCode::KEY_N;
        case GLFW_KEY_O:
            return KeyCode::KEY_O;
        case GLFW_KEY_P:
            return KeyCode::KEY_P;
        case GLFW_KEY_Q:
            return KeyCode::KEY_Q;
        case GLFW_KEY_R:
            return KeyCode::KEY_R;
        case GLFW_KEY_S:
            return KeyCode::KEY_S;
        case GLFW_KEY_T:
            return KeyCode::KEY_T;
        case GLFW_KEY_U:
            return KeyCode::KEY_U;
        case GLFW_KEY_V:
            return KeyCode::KEY_V;
        case GLFW_KEY_W:
            return KeyCode::KEY_W;
        case GLFW_KEY_X:
            return KeyCode::KEY_X;
        case GLFW_KEY_Y:
            return KeyCode::KEY_Y;
        case GLFW_KEY_Z:
            return KeyCode::KEY_Z;
        case GLFW_KEY_LEFT_BRACKET:
            return KeyCode::KEY_LEFT_BRACKET;
        case GLFW_KEY_BACKSLASH:
            return KeyCode::KEY_BACKSLASH;
        case GLFW_KEY_RIGHT_BRACKET:
            return KeyCode::KEY_RIGHT_BRACKET;
        case GLFW_KEY_GRAVE_ACCENT:
            return KeyCode::KEY_GRAVE_ACCENT;
        case GLFW_KEY_WORLD_1:
            return KeyCode::KEY_WORLD_1;
        case GLFW_KEY_WORLD_2:
            return KeyCode::KEY_WORLD_2;
        case GLFW_KEY_ESCAPE:
            return KeyCode::KEY_ESCAPE;
        case GLFW_KEY_ENTER:
            return KeyCode::KEY_ENTER;
        case GLFW_KEY_TAB:
            return KeyCode::KEY_TAB;
        case GLFW_KEY_BACKSPACE:
            return KeyCode::KEY_BACKSPACE;
        case GLFW_KEY_INSERT:
            return KeyCode::KEY_INSERT;
        case GLFW_KEY_DELETE:
            return KeyCode::KEY_DELETE;
        case GLFW_KEY_RIGHT:
            return KeyCode::KEY_RIGHT;
        case GLFW_KEY_LEFT:
            return KeyCode::KEY_LEFT;
        case GLFW_KEY_DOWN:
            return KeyCode::KEY_DOWN;
        case GLFW_KEY_UP:
            return KeyCode::KEY_UP;
        case GLFW_KEY_PAGE_UP:
            return KeyCode::KEY_PAGE_UP;
        case GLFW_KEY_PAGE_DOWN:
            return KeyCode::KEY_PAGE_DOWN;
        case GLFW_KEY_HOME:
            return KeyCode::KEY_HOME;
        case GLFW_KEY_END:
            return KeyCode::KEY_END;
        case GLFW_KEY_CAPS_LOCK:
            return KeyCode::KEY_CAPS_LOCK;
        case GLFW_KEY_SCROLL_LOCK:
            return KeyCode::KEY_SCROLL_LOCK;
        case GLFW_KEY_NUM_LOCK:
            return KeyCode::KEY_NUM_LOCK;
        case GLFW_KEY_PRINT_SCREEN:
            return KeyCode::KEY_PRINT_SCREEN;
        case GLFW_KEY_PAUSE:
            return KeyCode::KEY_PAUSE;
        case GLFW_KEY_F1:
            return KeyCode::KEY_F1;
        case GLFW_KEY_F2:
            return KeyCode::KEY_F2;
        case GLFW_KEY_F3:
            return KeyCode::KEY_F3;
        case GLFW_KEY_F4:
            return KeyCode::KEY_F4;
        case GLFW_KEY_F5:
            return KeyCode::KEY_F5;
        case GLFW_KEY_F6:
            return KeyCode::KEY_F6;
        case GLFW_KEY_F7:
            return KeyCode::KEY_F7;
        case GLFW_KEY_F8:
            return KeyCode::KEY_F8;
        case GLFW_KEY_F9:
            return KeyCode::KEY_F9;
        case GLFW_KEY_F10:
            return KeyCode::KEY_F10;
        case GLFW_KEY_F11:
            return KeyCode::KEY_F11;
        case GLFW_KEY_F12:
            return KeyCode::KEY_F12;
        case GLFW_KEY_F13:
            return KeyCode::KEY_F13;
        case GLFW_KEY_F14:
            return KeyCode::KEY_F14;
        case GLFW_KEY_F15:
            return KeyCode::KEY_F15;
        case GLFW_KEY_F16:
            return KeyCode::KEY_F16;
        case GLFW_KEY_F17:
            return KeyCode::KEY_F17;
        case GLFW_KEY_F18:
            return KeyCode::KEY_F18;
        case GLFW_KEY_F19:
            return KeyCode::KEY_F19;
        case GLFW_KEY_F20:
            return KeyCode::KEY_F20;
        case GLFW_KEY_F21:
            return KeyCode::KEY_F21;
        case GLFW_KEY_F22:
            return KeyCode::KEY_F22;
        case GLFW_KEY_F23:
            return KeyCode::KEY_F23;
        case GLFW_KEY_F24:
            return KeyCode::KEY_F24;
        case GLFW_KEY_F25:
            return KeyCode::KEY_F25;
        case GLFW_KEY_KP_0:
            return KeyCode::KEY_KP_0;
        case GLFW_KEY_KP_1:
            return KeyCode::KEY_KP_1;
        case GLFW_KEY_KP_2:
            return KeyCode::KEY_KP_2;
        case GLFW_KEY_KP_3:
            return KeyCode::KEY_KP_3;
        case GLFW_KEY_KP_4:
            return KeyCode::KEY_KP_4;
        case GLFW_KEY_KP_5:
            return KeyCode::KEY_KP_5;
        case GLFW_KEY_KP_6:
            return KeyCode::KEY_KP_6;
        case GLFW_KEY_KP_7:
            return KeyCode::KEY_KP_7;
        case GLFW_KEY_KP_8:
            return KeyCode::KEY_KP_8;
        case GLFW_KEY_KP_9:
            return KeyCode::KEY_KP_9;
        case GLFW_KEY_KP_DECIMAL:
            return KeyCode::KEY_KP_DECIMAL;
        case GLFW_KEY_KP_DIVIDE:
            return KeyCode::KEY_KP_DIVIDE;
        case GLFW_KEY_KP_MULTIPLY:
            return KeyCode::KEY_KP_MULTIPLY;
        case GLFW_KEY_KP_SUBTRACT:
            return KeyCode::KEY_KP_SUBTRACT;
        case GLFW_KEY_KP_ADD:
            return KeyCode::KEY_KP_ADD;
        case GLFW_KEY_KP_ENTER:
            return KeyCode::KEY_KP_ENTER;
        case GLFW_KEY_KP_EQUAL:
            return KeyCode::KEY_KP_EQUAL;
        case GLFW_KEY_LEFT_SHIFT:
            return KeyCode::KEY_LEFT_SHIFT;
        case GLFW_KEY_LEFT_CONTROL:
            return KeyCode::KEY_LEFT_CONTROL;
        case GLFW_KEY_LEFT_ALT:
            return KeyCode::KEY_LEFT_ALT;
        case GLFW_KEY_LEFT_SUPER:
            return KeyCode::KEY_LEFT_SUPER;
        case GLFW_KEY_RIGHT_SHIFT:
            return KeyCode::KEY_RIGHT_SHIFT;
        case GLFW_KEY_RIGHT_CONTROL:
            return KeyCode::KEY_RIGHT_CONTROL;
        case GLFW_KEY_RIGHT_ALT:
            return KeyCode::KEY_RIGHT_ALT;
        case GLFW_KEY_RIGHT_SUPER:
            return KeyCode::KEY_RIGHT_SUPER;
        case GLFW_KEY_MENU:
            return KeyCode::KEY_MENU;
        default:
            assert(printf("Unknown key: %i", key) && false);
    }
}

input::KeyEvent convertKeyCode(int key, int action) {
    return input::KeyEvent(convertKey(key), convertAction(action));
}

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr