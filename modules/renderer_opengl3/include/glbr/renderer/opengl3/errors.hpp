#pragma once

#include <glbr/logging/logging.hpp>

#include <glad/glad.h>

#ifndef NDEBUG
#define GL_VERIFY(cmd)                                                                                          \
    ([&]() {                                                                                                    \
        struct __GL_VERIFY {                                                                                    \
            ~__GL_VERIFY() noexcept(false) { glbr::renderer::opengl3::glCheckError(#cmd, __FILE__, __LINE__); } \
        } __GL_VERIFY;                                                                                          \
        return cmd;                                                                                             \
    }())
#else
#define GL_VERIFY(cmd) (cmd)
#endif

namespace glbr {
namespace renderer {
namespace opengl3 {

#ifndef NDEBUG

inline void glCheckError(const char *cmd, const char *file, int line) {
    if (GLenum err = glGetError()) {
        logging::error("GL ERROR: {} operation: {} at: {}:{}", err, cmd, file, line);
    }
}

#endif

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr