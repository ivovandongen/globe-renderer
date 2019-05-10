#pragma once

#include <glbr/logging/logging.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

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
        logging::debug("Initializing GLFW");
        if (!glfwInit()) {
            // Initialization failed
            logging::error("Failed to initialize GLFW");
            throw std::runtime_error("Failed to initialize GLFW");
        }
    };
    ~GLFWSystem() {
        logging::debug("Terminating GLFW");
        glfwTerminate();
    };
};

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr