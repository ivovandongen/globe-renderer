#include <glbr/input/events/key_event.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include "map_2d.hpp"

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

        return d.dispatch<KeyEvent>([&](KeyEvent& e) {
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
    });

    // Render function
    auto renderFn = [&](renderer::Context& context) {
        // Clear the scene
        context.clear(clearState);

        auto bounds = map.bounds();
        logging::debug("Bounds: ne:{},{} sw:{},{}, zoom: {}",
                       bounds.ne().x(),
                       bounds.ne().y(),
                       bounds.sw().x(),
                       bounds.sw().y(),
                       map.zoom());
    };

    // Update function
    auto updateFn = [&](auto interval) {};

    // Runloop
    window.run(renderFn, updateFn, 60);
}
