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
    struct NotSet {
        bool operator==(const NotSet&) const { return true; }
        bool operator!=(const NotSet&) const { return false; }
    };
    using Value = core::variant<NotSet, bool, unsigned int, int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

public:
    explicit Uniform(std::string name) : name_(std::move(name)) {}

    virtual ~Uniform() = default;

    const Value& value() const { return value_; }

    Uniform& operator=(const Value& value) {
        if (value != value_) {
            dirty_ = true;
            value_ = value;
        }

        return *this;
    }

    void apply() {
        if (dirty_) {
            if (!value_.is<NotSet>()) {
                logging::debug("Setting uniform {}", name_);
                doApply(value_);
                dirty_ = false;
            } else {
                logging::error("Uniform {} has no value", name_);
            }
        }
    }

protected:
    virtual void doApply(const Value& value) = 0;

private:
    std::string name_;
    Value value_;
    bool dirty_{true};
};

}  // namespace renderer
}  // namespace glbr