#include "subdivision.hpp"

#include <glbr/core/geometry/mesh.hpp>
#include <glbr/core/maths.hpp>
#include <glbr/imgui/imgui_layer.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/scene/camera/orbiting_camera_ctrl.hpp>
#include <glbr/scene/renderables/axis_renderable.hpp>

#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <memory>

using namespace glbr;
using namespace glbr::core;
using namespace glbr::core::geometry;
using namespace glbr::input;
using namespace glbr::renderer;

struct Options {
    bool animate = false;
    bool showAxis = true;
    bool showGrid = false;
    bool nightMode = false;
};

int main() {
    int width = 640, height = 480;

    // Mesh can be created without a current context
    auto mesh = subdivision(5);

    logging::setLevel(logging::Level::DEBUG);
    logging::info("Starting app");

    // Create the window
    glfw::GlfwGraphicsWindow window{width, height};

    // Set up the graphics device
    auto &device = opengl3::DeviceOpenGL3::instance();

    // Set up scene state
    SceneState sceneState(width, height, window.pixelRatio());
    sceneState.camera().position({0, 0, 3});

    // Add ImGui ui
    imgui::ImGuiLayer imguiLayer{window};

    // Set up camera controller
    scene::OrbitingCameraController cameraCtrl{sceneState.camera(), window};
    auto camHandlerRegistration = window.registerHandler(cameraCtrl);

    // Create the pipeline
    std::shared_ptr<Pipeline> pipeline =
        device.createPipeline(io::readFile("resources/vertex.glsl"), io::readFile("resources/fragment.glsl"));

    // Create a vertex array from the mesh
    std::shared_ptr<VertexArray> vertexArray = window.context().createVertexArray(*mesh);

    // Add a texture to overlay on the globe
    std::shared_ptr<Texture2D> globeTexture =
        device.createTexture2D(Image{"resources/NE2_50M_SR_W_4096.jpg", true}, false);
    std::shared_ptr<Texture2D> globeTextureNight =
        device.createTexture2D(Image{"resources/land_ocean_ice_lights_2048.jpg", true}, false);
    std::shared_ptr<TextureSampler> globeTextureSampler = device.createTextureSampler(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP);

    pipeline->uniforms()["bltin_texture0"] = 0;

    // Basic model matrix around the origin (rotated so the north pole is pointing straight up)
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
    model = glm::rotate(model, deg2rad(-90.f), {1.f, 0.f, 0.f});

    // Create an axis renderable
    scene::renderables::AxisRenderable axis{10};
    axis.init(window.context());

    renderer::ClearState clearState{ClearBuffers::COLOR, {0, 1, 1, 1}};

    // Add a control widget
    Options options;
    imguiLayer.addRenderable([&options]() {
        ImGui::SetNextWindowPos({0, 0});
        ImGui::SetNextWindowSize({180, 120});
        ImGui::Begin("Globe Controls", nullptr, ImGuiWindowFlags_None);
        ImGui::Checkbox("Animate", &options.animate);
        ImGui::Checkbox("Show axis", &options.showAxis);
        ImGui::Checkbox("Show globe grid", &options.showGrid);
        ImGui::Checkbox("Night mode", &options.nightMode);
        ImGui::End();
    });

    imguiLayer.init(window.context());

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene //
        clearState.color = {1., 1., 1., 1.};
        context.clear(clearState);

        if (options.showAxis) {
            // Draw the axis //
            axis.render(context, sceneState);
        }

        // Draw the model //

        sceneState.modelMatrix(model);

        // Switch textures
        if (options.nightMode) {
            window.context().textureUnits()[0](globeTextureNight, globeTextureSampler);
        } else {
            window.context().textureUnits()[0](globeTexture, globeTextureSampler);
        }

        auto rasterization = options.showGrid ? RasterizationMode::LINE : RasterizationMode::FILL;
        context.draw(mesh->primitiveType(),
                     {{rasterization, {true, CullFace::BACK, mesh->windingOrder()}}, pipeline, vertexArray},
                     sceneState);

        // Draw the ui
        imguiLayer.render(context, sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        if (options.animate) {
            cameraCtrl.rotateBy(0, float(M_2_PI) / 50.f * (interval.count() / 16666666));
        }
    };

    // Resize listener
    window.context().setOnResizeListener([&](float width, float height) {
        // Update scene state
        sceneState.viewport(width, height);
    });

    // Runloop
    window.run(renderFn, updateFn, 60);
}
