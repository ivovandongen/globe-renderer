#include <glbr/imgui/imgui_backend.hpp>

#include <glbr/logging/logging.hpp>

#include <imgui.h>

namespace glbr {
namespace imgui {

std::shared_ptr<ImGuiBackend> ImGuiBackend::instance() {
    // TODO: thread safe initialization?
    static std::weak_ptr<ImGuiBackend> weak;
    auto pool = weak.lock();
    if (!pool) {
        // Either use make_shared OR have a private constructor...
        weak = pool = std::shared_ptr<ImGuiBackend>(new ImGuiBackend());
    }
    return pool;
}

ImGuiBackend::ImGuiBackend() {
    logging::info("Setting up ImGui backend");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.BackendPlatformName = "GLBR";
    io.BackendRendererName = "Globe Renderer";

    // Enable Keyboard Controls
    //    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // TODO: setup keymap

    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;  // We can honor the ImDrawCmd::VtxOffset field, allowing
                                                                // for large meshes.

    // Build atlas
    unsigned char* tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);
}

ImGuiBackend::~ImGuiBackend() {
    logging::info("Tearing down ImGui backend");
}

void ImGuiBackend::operator()(core::Event& event) {
    // Handle mouse and key events
}

}  // namespace imgui
}  // namespace glbr