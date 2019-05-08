#pragma once

#include <glbr/core/variant.hpp>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>
#include <utility>

// TODO type checking

namespace glbr {
namespace renderer {

class Uniform {
public:
    using Value = core::variant<bool, unsigned int, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

public:
    explicit Uniform(std::string name) : _name(std::move(name)) {}

    virtual ~Uniform() = default;

    const Value& value() const { return _value; }

    Uniform& operator=(const Value& value) {
        if (value != _value) {
            _dirty = true;
            _value = value;
        }

        return *this;
    }

    void apply() {
        if (_dirty) {
            doApply(_value);
            _dirty = false;
        }
    }

protected:
    virtual void doApply(const Value& value) = 0;

private:
    std::string _name;
    Value _value;
    bool _dirty{false};
};

}  // namespace renderer
}  // namespace glbr