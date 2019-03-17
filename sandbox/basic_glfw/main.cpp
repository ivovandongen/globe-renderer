#include <glad/glad.h>

#include <renderer/glfw/graphics_window_glfw.hpp>

#include <iostream>

int main() {
    int width = 640, height = 480;

    renderer::glfw::GlfwGraphicsWindow win{width, height};

    win.run();

    glfwTerminate();
}
