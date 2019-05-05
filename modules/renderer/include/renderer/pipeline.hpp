#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <string>

namespace renderer {

class Pipeline {
public:
    virtual ~Pipeline() = default;

    virtual void bind() = 0;

    virtual void inline setUniform(const std::string &name, bool value) const = 0;

    virtual void inline setUniform(const std::string &name, unsigned int value) const = 0;

    virtual void inline setUniform(const std::string &name, int value) const = 0;

    virtual void inline setUniform(const std::string &name, float value) const = 0;

    virtual void inline setUniform(const std::string &name, float x, float y) const = 0;

    virtual void inline setUniform(const std::string &name, float x, float y, float z) const = 0;

    virtual void inline setUniform(const std::string &name, float x, float y, float z, float w) const = 0;

    virtual void inline setUniform(const std::string &name, glm::vec2 value) const = 0;

    virtual void inline setUniform(const std::string &name, glm::vec3 value) const = 0;

    virtual void inline setUniform(const std::string &name, glm::vec4 value) const = 0;

    virtual void inline setUniform(const std::string &name, glm::mat4 value) const = 0;
};

} // namespace renderer