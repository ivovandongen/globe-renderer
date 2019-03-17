#pragma once

#include <renderer/shader_program.hpp>

#include <memory>
#include <string>

namespace renderer {

class Device {
public:

    virtual ~Device();

    std::unique_ptr<GraphicsWindow> createWindow(int width, int height, string title, WindowType windowType)

    std::unique_ptr<ShaderProgram> createShaderProgram(const std::string &vertexSource, const std::string &fragmentSource);

private:
    Device() = default;
};

}