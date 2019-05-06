#include <utility>

#pragma once

#include <string>

namespace glbr {
namespace renderer {

class ShaderVertexAttribute {
public:
    ShaderVertexAttribute(std::string name, int location) : _name(std::move(name)), _location(location){};
    ~ShaderVertexAttribute() = default;

    const std::string& name() const { return _name; }
    int location() const { return _location; }

private:
    std::string _name{};
    int _location{-1};
};

}  // namespace renderer
}  // namespace glbr