#include <utility>

#pragma once

#include <string>

namespace glbr {
namespace renderer {

class ShaderVertexAttribute {
public:
    ShaderVertexAttribute(std::string name, int location) : name_(std::move(name)), location_(location){};
    ~ShaderVertexAttribute() = default;

    const std::string& name() const { return name_; }
    int location() const { return location_; }

private:
    std::string name_{};
    int location_{-1};
};

}  // namespace renderer
}  // namespace glbr