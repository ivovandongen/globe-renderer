#include <glbr/geo/tiles/tile_cover.hpp>
#include <glbr/imgui/imgui_layer.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_button_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
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

    // IMGui layer
    imgui::ImGuiLayer imguiLayer{window};
    imguiLayer.addRenderable([&]() {
        static std::array<char, 10> buf;
        ImGui::Begin("Map state", nullptr, ImGuiWindowFlags_None);
        auto bounds = map.bounds();
        ImGui::Text("Bounds: [%.3f,%.3f],[%.3f,%.3f]",
                    bounds.sw().lng(),
                    bounds.sw().lat(),
                    bounds.ne().lng(),
                    bounds.ne().lat());
        auto center = map.center();
        ImGui::Text("Center: [%.3f,%.3f]", center.lng(), center.lat());
        float zoom = map.zoom();
        if (ImGui::SliderFloat("", &zoom, map.minZoom(), 22, "Zoom: %.3f")) {
            map.zoom(zoom);
        }
        ImGui::Text("Min Zoom: %.3f", map.minZoom());
        ImGui::End();
    });
    imguiLayer.init(window.context());

    // Event handlers
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

        // Mouse drag handler
        static Position dragStartPosition = input::Position::INVALID;
        handled |= d.dispatch<MouseButtonEvent>([&](MouseButtonEvent& e) {
            if (e.state() == KeyState::PRESS) {
                // Record start position
                dragStartPosition = window.mousePosition();
            } else if (e.state() == KeyState::RELEASE) {
                // Move the map
                auto diff = window.mousePosition() - dragStartPosition;
                logging::info("Drag event: {}x{}", diff.x, diff.y);
                map.move(diff.x, diff.y);
            }
            return true;
        });

        return handled;
    });

    // Render function
    auto renderFn = [&](renderer::Context& context) {
        // Clear the scene
        context.clear(clearState);

        // Render gui
        imguiLayer.render(context, sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        imguiLayer.update(interval, sceneState);
        map.update();
    };

    // Runloop
    window.run(renderFn, updateFn, 60);
}
