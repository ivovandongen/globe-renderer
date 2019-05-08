#pragma once

#include <glbr/renderer/shaders/uniform.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class UniformOpenGL3 : public Uniform {
public:
    UniformOpenGL3(int location, std::string name /**TODO: type**/) : Uniform(std::move(name)), _location(location) {}

    ~UniformOpenGL3() override = default;

protected:
    void doApply(const Value& value) override;

private:
    int _location;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr