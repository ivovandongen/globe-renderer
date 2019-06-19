#pragma once

#include <glbr/renderer/device.hpp>
#include <glbr/renderer/shaders/auto_uniforms/draw_auto_uniform_factory.hpp>

#include <string>

namespace glbr {
namespace renderer {
namespace opengl3 {

class DeviceOpenGL3 : public Device {
public:
    using DrawAutoFactories = std::unordered_map<std::string, std::unique_ptr<DrawAutoUniformFactory>>;

    static DeviceOpenGL3 &instance();

    ~DeviceOpenGL3() override = default;

    std::unique_ptr<Pipeline> createPipeline(const std::string &vertexSource,
                                             const std::string &fragmentSource) const override;

    std::unique_ptr<Texture2D> createTexture2D(Texture2DDescription description, TextureTarget target) const override;

    std::unique_ptr<Texture2D> createTexture2D(const core::Image &image, bool generateMipmaps) const override;

    std::unique_ptr<Texture2D> createTexture2D(const core::Image &image, TextureFormat format,
                                               bool generateMipmaps) const override;

    std::unique_ptr<TextureSampler> createTextureSampler(TextureMinificationFilter filter,
                                                         TextureMagnificationFilter magnificationFilter, TextureWrap s,
                                                         TextureWrap t) const override;

    const DrawAutoFactories& drawAutoUniformFactories() const { return _drawAutoUniformFactories; }

private:
    DeviceOpenGL3();

private:
    DrawAutoFactories _drawAutoUniformFactories;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr