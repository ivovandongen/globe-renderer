#include <glbr/imgui/imgui_backend.hpp>

#include <glbr/input/events/char_event.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_button_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>

#include <imgui.h>

namespace glbr {
namespace imgui {

std::shared_ptr<ImGuiBackend> ImGuiBackend::Instance(core::EventProducer& eventProducer) {
    // TODO: thread safe initialization?
    static std::weak_ptr<ImGuiBackend> weak;
    auto pool = weak.lock();
    if (!pool) {
        // Either use make_shared OR have a private constructor...
        weak = pool = std::shared_ptr<ImGuiBackend>(new ImGuiBackend(eventProducer));
    }
    return pool;
}

ImGuiBackend::ImGuiBackend(core::EventProducer& eventProducer) {
    using namespace input;

    logging::info("Setting up ImGui backend");
    handlerRegistration_ = eventProducer.registerHandler(*this);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.BackendPlatformName = "GLBR";
    io.BackendRendererName = "Globe Renderer";

    // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Keyboard mapping. ImGui will use those indices to peek into the io.KeysDown[] array.
    io.KeyMap[ImGuiKey_Tab] = (int)KeyCode::KEY_TAB;
    io.KeyMap[ImGuiKey_LeftArrow] = (int)KeyCode::KEY_LEFT;
    io.KeyMap[ImGuiKey_RightArrow] = (int)KeyCode::KEY_RIGHT;
    io.KeyMap[ImGuiKey_UpArrow] = (int)KeyCode::KEY_UP;
    io.KeyMap[ImGuiKey_DownArrow] = (int)KeyCode::KEY_DOWN;
    io.KeyMap[ImGuiKey_PageUp] = (int)KeyCode::KEY_PAGE_UP;
    io.KeyMap[ImGuiKey_PageDown] = (int)KeyCode::KEY_PAGE_DOWN;
    io.KeyMap[ImGuiKey_Home] = (int)KeyCode::KEY_HOME;
    io.KeyMap[ImGuiKey_End] = (int)KeyCode::KEY_END;
    io.KeyMap[ImGuiKey_Insert] = (int)KeyCode::KEY_INSERT;
    io.KeyMap[ImGuiKey_Delete] = (int)KeyCode::KEY_DELETE;
    io.KeyMap[ImGuiKey_Backspace] = (int)KeyCode::KEY_BACKSPACE;
    io.KeyMap[ImGuiKey_Space] = (int)KeyCode::KEY_SPACE;
    io.KeyMap[ImGuiKey_Enter] = (int)KeyCode::KEY_ENTER;
    io.KeyMap[ImGuiKey_Escape] = (int)KeyCode::KEY_ESCAPE;
    io.KeyMap[ImGuiKey_A] = (int)KeyCode::KEY_A;
    io.KeyMap[ImGuiKey_C] = (int)KeyCode::KEY_C;
    io.KeyMap[ImGuiKey_V] = (int)KeyCode::KEY_V;
    io.KeyMap[ImGuiKey_X] = (int)KeyCode::KEY_X;
    io.KeyMap[ImGuiKey_Y] = (int)KeyCode::KEY_Y;
    io.KeyMap[ImGuiKey_Z] = (int)KeyCode::KEY_Z;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // We can honor the ImDrawCmd::VtxOffset field, allowing
    // for large meshes.
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

    // Build atlas
    unsigned char* tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);
}

ImGuiBackend::~ImGuiBackend() {
    logging::info("Tearing down ImGui backend");
}

void ImGuiBackend::operator()(core::Event& event) {
    using namespace input;
    ImGuiIO& io = ImGui::GetIO();

    // Handle mouse and key events
    core::EventDispatcher d{event};

    d.dispatch<KeyEvent>([&](KeyEvent& e) {
        if (e.state() == KeyState::PRESS) {
            io.KeysDown[(int)e.keyCode()] = true;
        } else if (e.state() == KeyState::RELEASE) {
            io.KeysDown[(int)e.keyCode()] = false;
        }

        // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[(int)KeyCode::KEY_LEFT_CONTROL] || io.KeysDown[(int)KeyCode::KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[(int)KeyCode::KEY_LEFT_SHIFT] || io.KeysDown[(int)KeyCode::KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[(int)KeyCode::KEY_LEFT_ALT] || io.KeysDown[(int)KeyCode::KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[(int)KeyCode::KEY_LEFT_SUPER] || io.KeysDown[(int)KeyCode::KEY_RIGHT_SUPER];

        return io.WantCaptureKeyboard;
    });

    d.dispatch<CharEvent>([&](CharEvent& e) {
        io.AddInputCharacter(e.character());
        return io.WantCaptureKeyboard;
    });

    d.dispatch<MouseButtonEvent>([&](MouseButtonEvent& e) {
        if (e.state() == KeyState::PRESS) {
            io.MouseDown[(int)e.buttonCode()] = true;
        } else if (e.state() == KeyState::RELEASE) {
            io.MouseDown[(int)e.buttonCode()] = false;
        }

        return io.WantCaptureMouse;
    });

    d.dispatch<MouseMoveEvent>([&](MouseMoveEvent& e) {
        io.MousePos = ImVec2(e.x(), e.y());
        return io.WantCaptureMouse;
    });

    d.dispatch<MouseScrollEvent>([&](MouseScrollEvent& e) {
        io.MouseWheelH += e.offsetX();
        io.MouseWheel += e.offsetY();
        return io.WantCaptureMouse;
    });
}

}  // namespace imgui
}  // namespace glbr