#include "glfw_events.hpp"
#include "glfw_system.hpp"

#include <glbr/input/events/key_event.hpp>
#include <glbr/input/events/mouse_button_event.hpp>
#include <glbr/input/events/mouse_move_event.hpp>
#include <glbr/input/events/mouse_scroll_event.hpp>
#include <glbr/logging/logging.hpp>
#include <glbr/renderer/glfw/graphics_window_glfw.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>

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
    : _system(GLFWSystem::init()), _size({width, height}) {
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
        logging::error("Failed to create GLFW window");
        return;
    }

    // Set the user pointer for use in callbacks
    glfwSetWindowUserPointer(_window, this);

    // Resize gl viewport on window viewport
    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow *window, int width, int height) {
        getGlfwGraphicsWindow(window)->_size = {width, height};
        getGlfwGraphicsWindow(window)->_context->viewport(width, height);
    });

    // Handle some input
    glfwSetKeyCallback(_window, [](GLFWwindow *window, int key, int, int action, int) {
        input::KeyEvent e = convertKeyEvent(key, action);
        emit(e, getGlfwGraphicsWindow(window)->_eventHandlers);
    });
    glfwSetMouseButtonCallback(_window, [](GLFWwindow *window, int button, int action, int) {
        input::MouseButtonEvent e = convertMouseButtonEvent(button, action);
        emit(e, getGlfwGraphicsWindow(window)->_eventHandlers);
    });
    glfwSetCursorPosCallback(_window, [](GLFWwindow *window, double x, double y) {
        input::MouseMoveEvent e{x, y};
        emit(e, getGlfwGraphicsWindow(window)->_eventHandlers);
    });
    glfwSetScrollCallback(_window, [](GLFWwindow *window, double x, double y) {
        input::MouseScrollEvent e{x, y};
        emit(e, getGlfwGraphicsWindow(window)->_eventHandlers);
    });

    // Make the context current for this thread
    makeContextCurrent();

    // Load glad
    if (!gladLoadGL()) {
        logging::error("Could not initialize GLAD");
        return;
    }

    // Enable vsync
    if (vsync) {
        glfwSwapInterval(1);
    }

    // Print gl version
    auto version = glGetString(GL_VERSION);
    logging::info("Using OpenGL version: {}", version);

    // Initialize our Context
    _context = std::make_unique<opengl3::ContextOpenGL3>(*this);

    if (type != WindowType::FullScreen) {
        // Position window in the center
        const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowPos(_window, (videoMode->width - width) / 2, (videoMode->height - height) / 2);
    }
};

GlfwGraphicsWindow::~GlfwGraphicsWindow() {
    logging::debug("Closing GLFW window");
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

void GlfwGraphicsWindow::run(const RenderFN &onRenderFrame, const UpdateFN &onUpdateFrame, double updateRate) {
    auto updateIntervalNS = 1 / updateRate * 1000 * 1000 * 1000;
    auto lastUpdate = std::chrono::high_resolution_clock::now();

    // Keep running
    while (!glfwWindowShouldClose(_window)) {
        glfwPollEvents();

        auto now = std::chrono::high_resolution_clock::now();
        auto interval = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastUpdate);
        if (interval.count() > updateIntervalNS) {
            lastUpdate = now;
            onUpdateFrame(interval);
        }

        onRenderFrame(*_context);

        glfwSwapBuffers(_window);
    }
}

Context &GlfwGraphicsWindow::context() const {
    return *_context;
}

void GlfwGraphicsWindow::close() {
    glfwSetWindowShouldClose(_window, GLFW_TRUE);
}

input::KeyState GlfwGraphicsWindow::keyState(input::KeyCode code) const {
    return convertKeyState(glfwGetKey(_window, convertKeyCode(code)));
}

input::KeyState GlfwGraphicsWindow::mouseButtonState(input::MouseButtonCode code) const {
    return convertKeyState(glfwGetMouseButton(_window, convertMouseButtonCode(code)));
}

input::Position GlfwGraphicsWindow::mousePosition() const {
    input::Position pos{};
    glfwGetCursorPos(_window, &pos.x, &pos.y);
    return pos;
}

class EventHandlerRegistrationImpl : public core::EventHandlerRegistration {
public:
    explicit EventHandlerRegistrationImpl(std::shared_ptr<core::EventHandlingFN> handler)
        : _handler(std::move(handler)) {}

    ~EventHandlerRegistrationImpl() override { logging::debug("Abandoning event handler registration"); }

private:
    std::shared_ptr<core::EventHandlingFN> _handler;
};

std::unique_ptr<core::EventHandlerRegistration> GlfwGraphicsWindow::registerHandler(
    const core::EventHandlingFN &handler) {
    auto sHandler = std::make_shared<core::EventHandlingFN>(handler);
    _eventHandlers.push_back(sHandler);
    return std::make_unique<EventHandlerRegistrationImpl>(std::move(sHandler));
}

}  // namespace glfw
}  // namespace renderer
}  // namespace glbr