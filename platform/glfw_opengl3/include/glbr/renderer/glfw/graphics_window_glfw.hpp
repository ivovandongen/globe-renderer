#pragma once

#include <glbr/renderer/context.hpp>
#include <glbr/renderer/graphics_window.hpp>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <functional>
#include <memory>

namespace glbr {
namespace renderer {
namespace glfw {

class GlfwGraphicsWindow : public GraphicsWindow {
public:
    GlfwGraphicsWindow(int width, int height, WindowType type = WindowType::Default, bool vsync = true);

    ~GlfwGraphicsWindow() override;

    Context &context() const override;

    void makeContextCurrent() const override;

    void run(const std::function<void(Context &)> &_onRenderFrame) override;

    void run(const std::function<void(Context &)> &onRenderFrame, const std::function<void()> &onUpdateFrame,
             double updateRate) override;

private:
    GLFWwindow *_window;
    std::unique_ptr<Context> _context;
};

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr