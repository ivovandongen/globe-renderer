#pragma once

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/shaders/uniform.hpp>

#include <memory>
#include <string>
#include <unordered_map>

namespace glbr {
namespace renderer {

class Uniforms {
private:
    using KeyedUniformCollection = std::unordered_map<std::string, std::unique_ptr<Uniform>>;

public:
    Uniforms() = default;

    Uniform& operator[](const std::string& key) {
        try {
            return *uniforms_.at(key);
        } catch (...) {
            logging::error("No uniform for key: {} ", key);
            throw std::runtime_error("No uniform for key: " + key);
        }
    }

    Uniform& at(const std::string& key) {
        try {
            return *uniforms_.at(key);
        } catch (...) {
            logging::error("No uniform for key: {} ", key);
            throw std::runtime_error("No uniform for key: " + key);
        }
    }

    const Uniform& at(const std::string& key) const {
        try {
            return *uniforms_.at(key);
        } catch (...) {
            logging::error("No uniform for key: {} ", key);
            throw std::runtime_error("No uniform for key: " + key);
        }
    }

    void add(const std::string& key, std::unique_ptr<Uniform> uniform) { uniforms_[key] = std::move(uniform); }

    void apply() {
        for (auto& entry : uniforms_) {
            entry.second->apply();
        }
    }

private:
    KeyedUniformCollection uniforms_;
};

}  // namespace renderer
}  // namespace glbr