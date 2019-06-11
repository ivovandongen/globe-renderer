#include "subdivision.hpp"

#include <glbr/core/geometry/mesh.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/io/file.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <array>
#include <glbr/input/events/key_event.hpp>
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

    SceneState sceneState(width, height);
    sceneState.camera().position({0, 0, 3});

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

    renderer::ClearState clearState{{0, 1, 1, 1}};

    const auto deg2rad = [](auto deg) -> float { return deg * M_PI / 180; };

    // Basic model matrix around the origin (rotated so the north pole is pointing straight up)
    const auto modelMatrix = [&deg2rad]() {
        auto model = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, 0.f));
        return glm::rotate(model, deg2rad(-90.f), {1.f, 0.f, 0.f});
    };

    glm::mat4 model = modelMatrix();

    bool animate = true;

    window.onEvent([&](auto &event) {
        core::EventDispatcher d(event);

        d.dispatch<KeyEvent>([&](KeyEvent &event) {
            if (event.state() == KeyState::RELEASE) {
                return false;
            }

            switch (event.keyCode()) {
                case KeyCode::KEY_A:
                    animate = !animate;
                    return true;
                case KeyCode::KEY_UP:
                    model = glm::rotate(model, deg2rad(10), {1.f, 0.f, 0.f});
                    return true;
                case KeyCode::KEY_DOWN:
                    model = glm::rotate(model, deg2rad(-10), {1.f, 0.f, 0.f});
                    return true;
                case KeyCode::KEY_LEFT:
                    model = glm::rotate(model, deg2rad(10), {0.f, 0.f, 1.f});
                    return true;
                case KeyCode::KEY_RIGHT:
                    model = glm::rotate(model, deg2rad(-10), {0.f, 0.f, 1.f});
                    return true;
                case KeyCode::KEY_R:
                    model = modelMatrix();
                    return true;
                default:
                    return false;
            }
        });

        // TODO: camera pan controls around world
        d.dispatch<MouseScrollEvent>([&sceneState](MouseScrollEvent &event) {
            if (event.offsetY() != 0) {
                sceneState.camera().zoom(event.offsetY());
                return true;
            }
            return false;
        });
    });

    // Render function
    auto renderFn = [&](renderer::Context &context) {
        // Clear the scene
        clearState.color = {1., 0, 1., 1};
        context.clear(clearState);

        // Update the MVP matrices
        pipeline->uniforms()["bltin_model"] = model;
        pipeline->uniforms()["bltin_view"] = sceneState.camera().viewMatrix();
        pipeline->uniforms()["bltin_projection"] = sceneState.projectionMatrix();

        // Draw the model
        // TODO: switch Rasterization mode
        context.draw({{RasterizationMode::Fill, {true, CullFace::BACK, mesh->windingOrder()}}, pipeline, vertexArray},
                     sceneState);
    };

    // Update function
    auto updateFn = [&](auto interval) {
        if (animate) {
            model =
                glm::rotate(model, float(M_2_PI) / 50.f * (interval.count() / 16666666), glm::vec3(0.0f, 0.0f, 1.0f));
        }
    };

    // Resize listener
    window.context().setOnResizeListener([&](float width, float height) {
        // Update projection matrix
        sceneState.viewport(width, height);
        pipeline->uniforms()["bltin_projection"] = sceneState.projectionMatrix();
    });

    // Runloop
    window.run(renderFn, updateFn, 60);
}
