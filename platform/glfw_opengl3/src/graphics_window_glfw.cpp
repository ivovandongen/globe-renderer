#include "glfw_events.hpp"
#include "glfw_system.hpp"

#include <glbr/input/events/char_event.hpp>
#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_button_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>
#include <glbr/renderer/window_resized_event.hpp>

#include <glad/glad.h>

#include <chrono>

namespace glbr {
namespace renderer {
namespace glfw {

void emit(core::Event &event, std::vector<std::weak_ptr<core::EventHandlingFN>> &handlers) {
    for (auto iter = handlers.begin(); iter != handlers.end();) {
        if (event.handled()) {
            break;
        }

        auto handler = iter->lock();
        if (handler) {
            (*handler)(event);
            ++iter;
        } else {
            logging::debug("Removing stale event handler registration");
            iter = handlers.erase(iter);
        }
    }
}

static GlfwGraphicsWindow *getGlfwGraphicsWindow(GLFWwindow *window) {
    return static_cast<GlfwGraphicsWindow *>(glfwGetWindowUserPointer(window));
}

GlfwGraphicsWindow::GlfwGraphicsWindow(int width, int height, WindowType type, bool vsync)
    : system_(GLFWSystem::Init()), size_({width, height}) {
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
        window_ = glfwCreateWindow(width, height, "Globe Renderer", glfwGetPrimaryMonitor(), nullptr);
    } else {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        window_ = glfwCreateWindow(width, height, "Globe Renderer", nullptr, nullptr);
    }

    if (!window_) {
        // Window or OpenGL context creation failed
        logging::error("Failed to create GLFW window");
        return;
    }

    // Set the user pointer for use in callbacks
    glfwSetWindowUserPointer(window_, this);

    // Resize gl viewport on window viewport
    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow *window, int width, int height) {
        auto *graphicsWindow = getGlfwGraphicsWindow(window);

        // Update the window size
        glfwGetWindowSize(window, &graphicsWindow->size_.width, &graphicsWindow->size_.height);

        // Update the pixel ratio
        graphicsWindow->pixelRatio_ = float(graphicsWindow->size_.width) / float(width);

        // Update the context viewport size
        graphicsWindow->context_->viewport(width, height);

        // Emit a window resized event
        WindowResizedEvent e{graphicsWindow->size_};
        emit(e, graphicsWindow->eventHandlers_);
    });

    // Handle some input
    glfwSetKeyCallback(window_, [](GLFWwindow *window, int key, int, int action, int) {
        input::KeyEvent e = convertKeyEvent(key, action);
        emit(e, getGlfwGraphicsWindow(window)->eventHandlers_);
    });
    glfwSetMouseButtonCallback(window_, [](GLFWwindow *window, int button, int action, int) {
        input::MouseButtonEvent e = convertMouseButtonEvent(button, action);
        emit(e, getGlfwGraphicsWindow(window)->eventHandlers_);
    });
    glfwSetCursorPosCallback(window_, [](GLFWwindow *window, double x, double y) {
        input::MouseMoveEvent e{x, y};
        emit(e, getGlfwGraphicsWindow(window)->eventHandlers_);
    });
    glfwSetScrollCallback(window_, [](GLFWwindow *window, double x, double y) {
        input::MouseScrollEvent e{x, y};
        emit(e, getGlfwGraphicsWindow(window)->eventHandlers_);
    });
    glfwSetCharCallback(window_, [](GLFWwindow *window, input::CharEvent::Char c) {
        input::CharEvent e{c};
        emit(e, getGlfwGraphicsWindow(window)->eventHandlers_);
    });

    // Make the context current for this thread
    makeContextCurrent();

    // Load glad
    if (!gladLoadGL()) {
        logging::error("Could not initialize GLAD");
        return;
    }

    // Enable vsync
    glfwSwapInterval(vsync ? 1 : 0);

    // Print gl version
    auto version = glGetString(GL_VERSION);
    logging::info("Using OpenGL version: {}", version);

    // Initialize our Context
    context_ = std::make_shared<opengl3::ContextOpenGL3>(*this);

    // Determine pixel ratio
    pixelRatio_ = [&]() {
        int fbwidth, fbheight;
        glfwGetFramebufferSize(window_, &fbwidth, &fbheight);
        return float(width) / float(fbwidth);
    }();

    if (type != WindowType::FullScreen) {
        // Position window in the center
        const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(window_, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
    }
};

GlfwGraphicsWindow::~GlfwGraphicsWindow() {
    logging::debug("Closing GLFW window");
    glfwDestroyWindow(window_);
};

void GlfwGraphicsWindow::makeContextCurrent() const {
    glfwMakeContextCurrent(window_);
}

void GlfwGraphicsWindow::run(const std::function<void(Context &)> &onRenderFrame_) {
    // Keep running
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();

        onRenderFrame_(*context_);

        glfwSwapBuffers(window_);
    }
}

void GlfwGraphicsWindow::run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) {
    auto updateIntervalNS = 1. / updateRate;
    auto lastUpdate = std::chrono::high_resolution_clock::now();

    // Keep running
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();

        auto now = std::chrono::high_resolution_clock::now();
        auto interval = now - lastUpdate;
        std::chrono::duration<double> intervalS = interval;
        if (intervalS.count() > updateIntervalNS) {
            lastUpdate = now;
            onUpdateFrame(interval);
        }

        onRenderFrame(*context_);

        glfwSwapBuffers(window_);
    }
}

Context &GlfwGraphicsWindow::context() const {
    return *context_;
}

void GlfwGraphicsWindow::close() {
    glfwSetWindowShouldClose(window_, GLFW_TRUE);
}

input::KeyState GlfwGraphicsWindow::keyState(input::KeyCode code) const {
    return convertKeyState(glfwGetKey(window_, convertKeyCode(code)));
}

input::KeyState GlfwGraphicsWindow::mouseButtonState(input::MouseButtonCode code) const {
    return convertKeyState(glfwGetMouseButton(window_, convertMouseButtonCode(code)));
}

input::Position GlfwGraphicsWindow::mousePosition() const {
    input::Position pos{};
    glfwGetCursorPos(window_, &pos.x, &pos.y);
    return pos;
}

class EventHandlerRegistrationImpl : public core::EventHandlerRegistration {
public:
    explicit EventHandlerRegistrationImpl(std::shared_ptr<core::EventHandlingFN> handler)
        : handler_(std::move(handler)) {}

    ~EventHandlerRegistrationImpl() override { logging::debug("Abandoning event handler registration"); }

private:
    std::shared_ptr<core::EventHandlingFN> handler_;
};

std::unique_ptr<core::EventHandlerRegistration> GlfwGraphicsWindow::registerHandler(
    const core::EventHandlingFN &handler) {
    auto sHandler = std::make_shared<core::EventHandlingFN>(handler);
    eventHandlers_.push_back(sHandler);
    return std::make_unique<EventHandlerRegistrationImpl>(std::move(sHandler));
}

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr