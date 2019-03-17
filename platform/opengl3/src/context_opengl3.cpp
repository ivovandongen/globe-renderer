#include <renderer/opengl3/context_opengl3.hpp>

#include <glad/glad.h>

namespace renderer {
namespace opengl3 {


ContextOpenGL3::ContextOpenGL3(const GraphicsWindow &window)
        : _window(window) {

};

void ContextOpenGL3::makeCurrent() const {
    _window.makeContextCurrent();
}

void ContextOpenGL3::draw() {
    // TODO
}

void ContextOpenGL3::clear() {
    // TODO: dirty state
    // TODO: Define clear color
    glClearColor(1, 0, 1, 1);

    // TODO: other bits
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace opengl3
} // namespace renderer
