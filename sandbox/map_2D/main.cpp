#include <glbr/imgui/imgui_layer.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include "map_2d.hpp"

#include <imgui.h>

int main() {
    int width = 512, height = 512;

    using namespace glbr;
    using namespace glbr::core;
    using namespace glbr::input;
    using namespace glbr::renderer;

    logging::setLevel(logging::Level::DEBUG);

    SceneState sceneState(width, height);

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    window.context().setOnResizeListener([&](float width, float height) {
        // Update scene state
        sceneState.viewport(width, height);
    });

    // Set up the graphics device
    auto& device = opengl3::DeviceOpenGL3::instance();

    ClearState clearState{ClearBuffers::ALL, {1, 1, 1, 1}, {false}};

    Map2D map(width, height);

    // Resize listener
    window.context().setOnResizeListener([&](float width, float height) {
        // Update scene state
        sceneState.viewport(width, height);

        // Update map
        map.resize(width, height);
    });

    auto eventHandlerReg = window.registerHandler([&](Event& event) {
        EventDispatcher d(event);

        bool handled = d.dispatch<KeyEvent>([&](KeyEvent& e) {
            if (e.state() == KeyState::PRESS) {
                switch (e.keyCode()) {
                    case KeyCode::KEY_Q:
                        map.zoom(map.zoom() + 1);
                        return true;
                    case KeyCode::KEY_A:
                        map.zoom(map.zoom() - 1);
                        return true;
                    default:
                        return false;
                }
            }
            return false;
        });

        handled |= d.dispatch<MouseScrollEvent>([&](MouseScrollEvent& e) {
            logging::info("Scroll event: {}x{}", e.offsetX(), e.offsetY());
            map.zoom(map.zoom() - e.offsetY());
            return true;
        });

        return handled;
    });

    // IMGui layer
    imgui::ImGuiLayer imguiLayer{window};
    imguiLayer.addRenderable([&]() {
        static std::array<char, 10> buf;
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({float(width), 100});
        ImGui::Begin("Map state", nullptr, ImGuiWindowFlags_None);
        auto bounds = map.bounds();
        ImGui::Text("Bounds: [%.3f,%.3f],[%.3f,%.3f]",
                    bounds.ne().lng(),
                    bounds.ne().lat(),
                    bounds.sw().lng(),
                    bounds.sw().lat());
        float zoom = map.zoom();
        if (ImGui::SliderFloat("", &zoom, map.minZoom(), 22, "Zoom: %.3f")) {
            map.zoom(zoom);
        }
        ImGui::Text("Min Zoom: %.3f", map.minZoom());
        ImGui::End();
    });

    imguiLayer.init(window.context());

    // Render function
    auto renderFn = [&](renderer::Context& context) {
        // Clear the scene
        context.clear(clearState);

        // Render gui
        imguiLayer.render(context, sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) { imguiLayer.update(interval, sceneState); };

    // Runloop
    window.run(renderFn, updateFn, 60);
}
