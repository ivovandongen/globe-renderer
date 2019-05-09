#pragma once

#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>

#include <iostream>
#include <memory>

namespace glbr {
namespace renderer {
namespace glfw {

class GLFWSystem {
public:
    static std::shared_ptr<GLFWSystem> init() {
        // TODO: thread safe initialization
        static std::weak_ptr<GLFWSystem> weak;
        auto pool = weak.lock();
        if (!pool) {
            weak = pool = std::make_shared<GLFWSystem>();
        }
        return pool;
    }

    GLFWSystem() {
        if (!glfwInit()) {
            // Initialization failed
            std::cout << "Failed to initialize GLFW" << std::endl;
            throw std::runtime_error("Failed to initialize GLFW");
        }
    };
    ~GLFWSystem() { glfwTerminate(); };
};

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr