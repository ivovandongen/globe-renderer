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
                                             const std::string &fragmentSource) const override;

    std::unique_ptr<Texture2D> createTexture2D(const core::Image &image, bool generateMipmaps) const override;

    std::unique_ptr<Texture2D> createTexture2D(const core::Image &image, TextureFormat format,
                                               bool generateMipmaps) const override;

    std::unique_ptr<TextureSampler> createTextureSampler(TextureMinificationFilter filter,
                                                         TextureMagnificationFilter magnificationFilter, TextureWrap s,
                                                         TextureWrap t) const override;

private:
    DeviceOpenGL3() = default;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr