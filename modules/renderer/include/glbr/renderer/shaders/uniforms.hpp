#pragma once

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

    Uniform& operator[](const std::string& key) { return *_uniforms.at(key); }
    Uniform& at(const std::string& key) { return *_uniforms.at(key); }
    const Uniform& at(const std::string& key) const { return *_uniforms.at(key); }

    void add(const std::string& key, std::unique_ptr<Uniform> uniform) { _uniforms[key] = std::move(uniform); }

    void apply() {
        for (auto& entry : _uniforms) {
            entry.second->apply();
        }
    }

private:
    KeyedUniformCollection _uniforms;
};

}  // namespace renderer
}  // namespace glbr