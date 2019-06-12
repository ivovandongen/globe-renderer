#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/graphics_window.hpp>

#include <functional>
#include <memory>

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

    void run(const RenderFN &_onRenderFrame) override;

    void run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) override;

    void registerHandler(const core::EventHandlingFN &handler) override {
        _eventHandlers.push_back(std::move(handler));
    }

    input::KeyState keyState(input::KeyCode code) const override;

    input::KeyState mouseButtonState(input::MouseButtonCode code) const override;

    input::Position mousePosition() const override;

    void close() override;

private:
    std::shared_ptr<GLFWSystem> _system;
    GLFWwindow *_window;
    std::unique_ptr<Context> _context;
    std::vector<core::EventHandlingFN> _eventHandlers;
};

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr