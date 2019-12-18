#pragma once

#include <glbr/renderer/graphics_window.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>

#include <functional>
#include <memory>
#include <vector>

class GLFWSystem;
class GLFWwindow;

namespace glbr {
namespace renderer {
namespace glfw {

class GlfwGraphicsWindow : public GraphicsWindow {
public:
    GlfwGraphicsWindow(int width, int height, WindowType type = WindowType::Default, bool vsync = true);

    ~GlfwGraphicsWindow() override;

    Context &context() const override;

    void makeContextCurrent() const override;

    core::Size2D<int> size() const override { return size_; }

    float pixelRatio() const override { return pixelRatio_; }

    void run(const RenderFN &onRenderFrame) override;

    void run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) override;

    std::unique_ptr<core::EventHandlerRegistration> registerHandler(const core::EventHandlingFN &handler) override;

    input::KeyState keyState(input::KeyCode code) const override;

    input::KeyState mouseButtonState(input::MouseButtonCode code) const override;

    input::Position mousePosition() const override;

    void close() override;

private:
    std::shared_ptr<GLFWSystem> system_;
    GLFWwindow *window_;
    std::shared_ptr<opengl3::ContextOpenGL3> context_;
    std::vector<std::weak_ptr<core::EventHandlingFN>> eventHandlers_;
    core::Size2D<int> size_;
    float pixelRatio_ = 1;
};

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr