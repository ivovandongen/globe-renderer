#include <renderer/glfw/graphics_window_glfw.hpp>
#include <renderer/opengl3/context_opengl3.hpp>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <iostream>

namespace {

bool init() {
    if (!glfwInit()) {
        // Initialization failed
        std::cout << "Failed to initialize GLFW" << std::endl;
        return false;
    }
    return true;
}

bool glfwInitialized = false;

} // namespace

namespace renderer {
namespace glfw {


GlfwGraphicsWindow::GlfwGraphicsWindow(int width, int height, WindowType type, bool vsync)
        : _context(std::make_unique<opengl3::ContextOpenGL3>(*this)) {

    if (!glfwInitialized) {
        init();
        glfwInitialized = true;
    }

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

    // Resize gl viewport on window resize
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *, int width, int height) {
        // TODO: call into context
        glViewport(0, 0, width, height);
    });


    // Handle some input
    glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int, int action, int) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    });

    if (type == WindowType::FullScreen) {
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

void GlfwGraphicsWindow::run() {
    // Keep running
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        // TODO: update freq + callback

        // TODO: onRenderFrame callback

        _context->clear();

        _context->draw();

        glfwSwapBuffers(_window);
    }
}

} // namespace glfw
} // namespace renderer