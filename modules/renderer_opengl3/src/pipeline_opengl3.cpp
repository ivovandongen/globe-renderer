#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>

#include <glm/gtc/type_ptr.hpp>

#include <glbr/renderer/opengl3/errors.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace {

inline std::string shaderType(GLenum type) {
    switch (type) {
        case GL_VERTEX_SHADER:
            return "Vertex";
        case GL_GEOMETRY_SHADER:
            return "Geometry";
        case GL_FRAGMENT_SHADER:
            return "Fragment";
        default:
            return "UNKNOWN";
    }
}

GLuint loadShader(GLuint program, const std::string &shaderSource, GLuint type) {
    GLuint shaderId = GL_VERIFY(glCreateShader(type));
    auto source = shaderSource.c_str();
    const GLint length = shaderSource.length();
    GL_VERIFY(glShaderSource(shaderId, 1, &source, &length));
    GL_VERIFY(glCompileShader(shaderId));
    GLint compileStatus;
    GL_VERIFY(glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus));
    if (compileStatus == GL_FALSE) {
        GLint maxLength = 0;
        GL_VERIFY(glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength));

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        GL_VERIFY(glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]));
        std::string message = std::string("Could not compile ") + shaderType(type) + " shader\n" + errorLog.data();
        std::cout << message << std::endl;
    }
    GL_VERIFY(glAttachShader(program, shaderId));

    return shaderId;
}

}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

PipelineOpenGL3::PipelineOpenGL3(const std::string &vert, const std::string &frag) {
    _id = GL_VERIFY(glCreateProgram());
    auto vertexShader = loadShader(_id, vert, GL_VERTEX_SHADER);
    auto fragmentShader = loadShader(_id, frag, GL_FRAGMENT_SHADER);

    GL_VERIFY(glLinkProgram(_id));
    GL_VERIFY(glValidateProgram(_id));
    GL_VERIFY(glDeleteShader(vertexShader));
    GL_VERIFY(glDeleteShader(fragmentShader));
}

PipelineOpenGL3::~PipelineOpenGL3() {
    GL_VERIFY(glDeleteProgram(_id));
}

void PipelineOpenGL3::bind() {
    GL_VERIFY(glUseProgram(_id));
}

void PipelineOpenGL3::setUniform(const std::string &name, bool value) const {
    // TODO: cache uniform locations
    GL_VERIFY(glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value));
}

void PipelineOpenGL3::setUniform(const std::string &name, unsigned int value) const {
    GL_VERIFY(glUniform1i(glGetUniformLocation(_id, name.c_str()), value));
}

void PipelineOpenGL3::setUniform(const std::string &name, int value) const {
    GL_VERIFY(glUniform1i(glGetUniformLocation(_id, name.c_str()), value));
}

void PipelineOpenGL3::setUniform(const std::string &name, float value) const {
    GL_VERIFY(glUniform1f(glGetUniformLocation(_id, name.c_str()), value));
}

void PipelineOpenGL3::setUniform(const std::string &name, float x, float y) const {
    GL_VERIFY(glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y));
}

void PipelineOpenGL3::setUniform(const std::string &name, float x, float y, float z) const {
    GL_VERIFY(glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z));
}

void PipelineOpenGL3::setUniform(const std::string &name, float x, float y, float z, float w) const {
    GL_VERIFY(glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w));
}

void PipelineOpenGL3::setUniform(const std::string &name, glm::vec2 value) const {
    GL_VERIFY(glUniform2f(glGetUniformLocation(_id, name.c_str()), value.x, value.y));
}

void PipelineOpenGL3::setUniform(const std::string &name, glm::vec3 value) const {
    GL_VERIFY(glUniform3f(glGetUniformLocation(_id, name.c_str()), value.x, value.y, value.z));
}

void PipelineOpenGL3::setUniform(const std::string &name, glm::vec4 value) const {
    GL_VERIFY(glUniform4f(glGetUniformLocation(_id, name.c_str()), value.x, value.y, value.z, value.w));
}

void PipelineOpenGL3::setUniform(const std::string &name, glm::mat4 value) const {
    GL_VERIFY(glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value)));
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
