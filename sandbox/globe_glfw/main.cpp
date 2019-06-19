#include "subdivision.hpp"

#include <glbr/core/geometry/mesh.hpp>
#include <glbr/core/maths.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/scene/camera/orbiting_camera_ctrl.hpp>
#include <glbr/scene/renderables/axis_renderable.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <memory>

using namespace glbr;
using namespace glbr::core;
using namespace glbr::core::geometry;
using namespace glbr::input;
using namespace glbr::renderer;

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
    SceneState sceneState(width, height);
    sceneState.camera().position({0, 0, 3});

    // Set up camera controller
    scene::OrbitingCameraController cameraCtrl{sceneState.camera(), window};
    window.registerHandler(cameraCtrl);

    // Add key controller
    bool animate = true;
    window.registerHandler([&](auto &event) {
        core::EventDispatcher d(event);

        d.dispatch<KeyEvent>([&](KeyEvent &event) {
            if (event.state() == KeyState::RELEASE) {
                return false;
            }

            switch (event.keyCode()) {
                case KeyCode::KEY_A:
                    animate = !animate;
                    return true;
                default:
                    return false;
            }
        });
    });

    // Create the pipeline
    std::shared_ptr<Pipeline> pipeline =
        device.createPipeline(io::readFile("resources/vertex.glsl"), io::readFile("resources/fragment.glsl"));

    // Create a vertex array from the mesh
    std::shared_ptr<VertexArray> vertexArray = window.context().createVertexArray(*mesh);

    // Add a texture to overlay on the globe
    // TODO switch textures
    window.context().textureUnits()[0].texture(
        device.createTexture2D(Image{"resources/NE2_50M_SR_W_4096.jpg", true}, false));
    window.context().textureUnits()[0].sampler(device.createTextureSampler(
        TextureMinificationFilter::LINEAR, TextureMagnificationFilter::LINEAR, TextureWrap::CLAMP, TextureWrap::CLAMP));

    pipeline->uniforms()["bltin_texture0"] = 0;

    // Basic model matrix around the origin (rotated so the north pole is pointing straight up)
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
    model = glm::rotate(model, deg2rad(-90), {1.f, 0.f, 0.f});

    // Create an axis renderable
    scene::renderables::AxisRenderable axis{10};
    axis.init(window.context());

    renderer::ClearState clearState{{0, 1, 1, 1}};

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene //
        clearState.color = {1., 1., 1., 1.};
        context.clear(clearState);

        // Draw the axis //
        axis.render(context, sceneState);

        // Draw the model //

        sceneState.modelMatrix(model);

        // TODO: switch Rasterization mode
        context.draw(mesh->primitiveType(),
                     {{RasterizationMode::Fill, {true, CullFace::BACK, mesh->windingOrder()}}, pipeline, vertexArray},
                     sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        if (animate) {
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
