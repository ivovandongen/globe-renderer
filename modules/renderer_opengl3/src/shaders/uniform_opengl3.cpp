#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/shaders/uniform_opengl3.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace {

struct ValueApplyVisitor {
    int location;

    void operator()(const float& value) { GL_VERIFY(glUniform1f(location, value)); }
    void operator()(const glm::vec2& value) { GL_VERIFY(glUniform2f(location, value.x, value.y)); }
    void operator()(const glm::vec3& value) { GL_VERIFY(glUniform3f(location, value.x, value.y, value.z)); }
    void operator()(const glm::vec4& value) { GL_VERIFY(glUniform4f(location, value.x, value.y, value.z, value.w)); }
    void operator()(const glm::mat4& value) {
        GL_VERIFY(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));
    }

    template <class IntType>
    void operator()(const IntType& value) {
        GL_VERIFY(glUniform1i(location, value));
    }
};

}  // namespace

namespace glbr {
namespace renderer {
namespace opengl3 {

void UniformOpenGL3::doApply(const Value& value) {
    core::apply_visitor(ValueApplyVisitor{_location}, value);
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr