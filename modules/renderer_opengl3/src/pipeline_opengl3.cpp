#include <glbr/renderer/opengl3/pipeline_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/device_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/shaders/uniform_opengl3.hpp>

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
        glbr::logging::error("Could not compile {} shader: {}", shaderType(type), errorLog.data());
    }
    GL_VERIFY(glAttachShader(program, shaderId));

    return shaderId;
}

}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

PipelineOpenGL3::PipelineOpenGL3(const std::string &vert, const std::string &frag) {
    id_ = GL_VERIFY(glCreateProgram());
    auto vertexShader = loadShader(id_, vert, GL_VERTEX_SHADER);
    auto fragmentShader = loadShader(id_, frag, GL_FRAGMENT_SHADER);

    GL_VERIFY(glLinkProgram(id_));
    GL_VERIFY(glValidateProgram(id_));
    GL_VERIFY(glDeleteShader(vertexShader));
    GL_VERIFY(glDeleteShader(fragmentShader));

    loadVertexAttributes();
    loadUniforms();
}

PipelineOpenGL3::~PipelineOpenGL3() {
    GL_VERIFY(glDeleteProgram(id_));
}

void PipelineOpenGL3::bind() const {
    GL_VERIFY(glUseProgram(id_));
}

void PipelineOpenGL3::loadVertexAttributes() {
    // Get number of active attributes
    int numberOfAttributes = 0;
    GL_VERIFY(glGetProgramiv(id_, GL_ACTIVE_ATTRIBUTES, &numberOfAttributes));

    if (numberOfAttributes == 0) {
        logging::debug("No vertex attributes to load");
        return;
    }

    // The the max name length of those attributes
    int nameMaxLength = 0;
    GL_VERIFY(glGetProgramiv(id_, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &nameMaxLength));

    // For each attribute, create a record
    std::vector<GLchar> nameBuffer;
    nameBuffer.resize(nameMaxLength);
    for (int i = 0; i < numberOfAttributes; i++) {
        int nameLength;
        int length;
        GLenum type;
        GL_VERIFY(glGetActiveAttrib(id_, i, nameMaxLength, &nameLength, &length, &type, nameBuffer.data()));
        // TODO: type
        int location = GL_VERIFY(glGetAttribLocation(id_, nameBuffer.data()));
        vertexAttributeBindings_.emplace_back(std::string{nameBuffer.data()}, location);
    }
}
void PipelineOpenGL3::loadUniforms() {
    int numUniforms;
    GL_VERIFY(glGetProgramiv(id_, GL_ACTIVE_UNIFORMS, &numUniforms));

    int nameMaxLength;
    GL_VERIFY(glGetProgramiv(id_, GL_ACTIVE_UNIFORM_MAX_LENGTH, &nameMaxLength));

    // For each attribute, create a record
    std::vector<GLchar> nameBuffer;
    nameBuffer.resize(nameMaxLength);

    for (int i = 0; i < numUniforms; ++i) {
        int nameLength;
        int length;
        GLenum type;
        GL_VERIFY(glGetActiveUniform(id_, i, nameMaxLength, &nameLength, &length, &type, nameBuffer.data()));
        // TODO: type
        std::string name(nameBuffer.data(), nameLength);
        int location = GL_VERIFY(glGetUniformLocation(id_, name.c_str()));
        uniforms_.add(name, std::make_unique<UniformOpenGL3>(location, name));

        // Check if this is an automatic uniform
        auto &drawAutoFactories = DeviceOpenGL3::Instance().drawAutoUniformFactories();
        auto drawAutoFactory = drawAutoFactories.find(name);
        if (drawAutoFactory != drawAutoFactories.end()) {
            logging::debug("Registering draw auto uniform: {}", name);
            drawAutoUniforms_.push_back((*drawAutoFactory->second)(uniforms_[name]));
        }
    }
}

void PipelineOpenGL3::clean(const Context &context, const DrawState &drawState, const SceneState &sceneState) {
    // Update draw automatic uniforms
    for (auto &dau : drawAutoUniforms_) {
        dau(context, drawState, sceneState);
    }

    // Apply uniforms
    uniforms_.apply();
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
