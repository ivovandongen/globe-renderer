#pragma once

#include <glbr/renderer/device.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class DeviceOpenGL3 : public Device {
public:
    static DeviceOpenGL3 &instance();

    ~DeviceOpenGL3() override = default;

    std::unique_ptr<Pipeline> createPipeline(const std::string &vertexSource,
                                             const std::string &fragmentSource) override;

private:
    DeviceOpenGL3() = default;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr