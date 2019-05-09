#include "glfw_system.hpp"

#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/context_opengl3.hpp>

#include <glad/glad.h>

#include <chrono>
#include <iostream>

namespace glbr {
namespace renderer {
namespace glfw {

static GlfwGraphicsWindow *getGlfwGraphicsWindow(GLFWwindow *window) {
    return static_cast<GlfwGraphicsWindow *>(glfwGetWindowUserPointer(window));
}

GlfwGraphicsWindow::GlfwGraphicsWindow(int width, int height, WindowType type, bool vsync)
    : _system(GLFWSystem::init()), _context(std::make_unique<opengl3::ContextOpenGL3>(*this)) {

    // TODO Move OpenGL specifics

    // Specify OpenGL version to use
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (type == WindowType::FullScreen) {
        _window = glfwCreateWindow(width, height, "Globe Renderer", glfwGetPrimaryMonitor(), nullptr);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        _window = glfwCreateWindow(width, height, "Globe Renderer", nullptr, nullptr);
    }

    if (!_window) {
        // Window or OpenGL context creation failed
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    // Set the user pointer for use in callbacks
    glfwSetWindowUserPointer(_window, this);

    // Resize gl viewport on window resize
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
        getGlfwGraphicsWindow(window)->_context->resize(width, height);
    });

    // Handle some input
    glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    if (type != WindowType::FullScreen) {
        // Position window in the center
        const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(_window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
    }

    // Make the context current for this thread
    _context->makeCurrent();

    // Load glad
    if (!gladLoadGL()) {
        std::cerr << "Could not initialize GLAD" << std::endl;
        return;
    }

    // Enable vsync
    if (vsync) {
        glfwSwapInterval(1);
    }

    // Print gl version
    auto version = glGetString(GL_VERSION);
    std::cout << "Using OpenGL version: " << version << std::endl;
};

GlfwGraphicsWindow::~GlfwGraphicsWindow() {
    glfwDestroyWindow(_window);
};

void GlfwGraphicsWindow::makeContextCurrent() const {
    glfwMakeContextCurrent(_window);
}

void GlfwGraphicsWindow::run(const std::function<void(Context &)> &_onRenderFrame) {
    // Keep running
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        _onRenderFrame(*_context);

        glfwSwapBuffers(_window);
    }
}

void GlfwGraphicsWindow::run(const std::function<void(Context &)> &onRenderFrame,
                             const std::function<void()> &onUpdateFrame, double updateRate) {
    auto updateIntervalNS = 1 / updateRate * 1000 * 1000 * 1000;
    auto lastUpdate = std::chrono::high_resolution_clock::now();

    // Keep running
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastUpdate).count() > updateIntervalNS) {
            lastUpdate = now;
            onUpdateFrame();
        }

        onRenderFrame(*_context);

        glfwSwapBuffers(_window);
    }
}

Context &GlfwGraphicsWindow::context() const {
    return *_context;
}

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr