#include <glbr/core/image.hpp>
#include <glbr/imgui/imgui_layer.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/textures/texture_sampler_opengl3.hpp>
#include <glbr/renderer/textures/texture2d.hpp>

#include <imgui.h>
#include <array>

int main() {
    int width = 640, height = 480;

    using namespace glbr;
    using namespace glbr::core;
    using namespace glbr::renderer;

    logging::setLevel(logging::Level::DEBUG);

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    SceneState sceneState(width, height, window.pixelRatio());

    window.context().setOnResizeListener([&](float width, float height) {
        // Update scene state
        sceneState.viewport(width, height);
    });

    // Set up the graphics device
    auto& device = opengl3::DeviceOpenGL3::Instance();

    ClearState clearState{ClearBuffers::ALL, {1, 1, 1, 1}, {false}};

    imgui::ImGuiLayer imguiLayer{window};

    // Add update rate widget
    std::vector<float> updateTimes;
    imguiLayer.addRenderable([&]() {
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({float(width), 100});
        ImGui::Begin("Update Rate", nullptr, ImGuiWindowFlags_Modal);

        float interval = updateTimes.empty() ? 0.f : updateTimes.back();
        if (interval > 0) {
            ImGui::Text("Application update rate %.3f ms/frame (%.1f FPS)", interval, 1000.f / interval);
        }

        // Plot some values
        ImGui::PlotLines("Frame Times", updateTimes.data(), updateTimes.size(), 0, nullptr, 0.f, 50.f);

        ImGui::End();
    });

    // Add render rate window
    imguiLayer.addRenderable([&]() {
        static std::array<char, 10> buf;
        ImGui::SetNextWindowPos({0, 100});
        ImGui::SetNextWindowSize({float(width), 100});
        auto& io = ImGui::GetIO();
        ImGui::Begin("Render rate", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Application render rate %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::InputText("string", buf.data(), buf.size());
        ImGui::End();
    });

    imguiLayer.init(window.context());

    // Add a debug event handler to see if event capturing works correctly
    auto handlerReg = window.registerHandler([](auto& event) {
        logging::debug("Event: {} (handled: {})", event.str(), event.handled());
        return false;
    });

    // Render function
    auto renderFn = [&](renderer::Context& context) {
        // Clear the scene
        context.clear(clearState);

        // Render the gui
        imguiLayer.render(context, sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        // Update img gui layer
        imguiLayer.update(interval, sceneState);

        updateTimes.push_back(std::chrono::duration_cast<std::chrono::duration<float>>(interval).count() * 1000);
        const float maxItems = 200;
        if (updateTimes.size() > maxItems) {
            updateTimes.erase(updateTimes.begin(), updateTimes.begin() + (updateTimes.size() - maxItems));
        }
    };

    // Runloop
    window.run(renderFn, updateFn, 60);
}
