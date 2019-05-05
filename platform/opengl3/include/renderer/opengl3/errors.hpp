#pragma once

#include <glad/glad.h>

#include <iostream>

#ifndef NDEBUG
#define GL_VERIFY(cmd) ([&]() { \
    struct __GL_VERIFY { \
        ~__GL_VERIFY() noexcept(false) { \
            renderer::opengl3::glCheckError(#cmd, __FILE__, __LINE__); \
        } \
    } __GL_VERIFY; \
    return cmd; \
}())
#else
#define GL_VERIFY(cmd) (cmd)
#endif

namespace renderer {
namespace opengl3 {

#ifndef NDEBUG

inline void glCheckError(const char *cmd, const char *file, int line) {
    if (GLenum err = glGetError()) {
        std::cout << "GL ERROR: " << err << " operation: " << cmd << " at: " << file << ":" << line;
    }
}

#endif

} // namespace opengl3
} // namespace renderer