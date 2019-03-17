#pragma once

#include <renderer/context.hpp>
#include <renderer/graphics_window.hpp>

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <memory>

namespace renderer {
namespace glfw {

class GlfwGraphicsWindow : public GraphicsWindow {
public:
    GlfwGraphicsWindow(int width, int height, WindowType type = WindowType::Default, bool vsync = true);

    ~GlfwGraphicsWindow() override;

    void makeContextCurrent() const override;

    void run() override;

private:
    GLFWwindow *_window;
    std::unique_ptr<Context> _context;
};

} // namespace glfw
} // namespace renderer