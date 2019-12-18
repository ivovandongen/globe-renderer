#pragma once

#include <glbr/renderer/textures/texture2d.hpp>
#include <glbr/renderer/textures/texture2d_description.hpp>
#include <glbr/renderer/textures/texture_target.hpp>

#include <glad/glad.h>

namespace glbr {
namespace renderer {
namespace opengl3 {

class Texture2DOpenGL3 : public Texture2D {
public:
    Texture2DOpenGL3(Texture2DDescription, TextureTarget);

    ~Texture2DOpenGL3() override;

    void bind() const override;

    void upload(const void *data) const override;

    bool operator==(const Texture2DOpenGL3 &other) const { return id_ == other.id_; }
    bool operator!=(const Texture2DOpenGL3 &other) const { return id_ != other.id_; }

private:
    GLuint id_{};
    GLenum target_;
    Texture2DDescription description_;
    std::shared_ptr<const core::Image> image_;
};

class Texture2DOpenGL3WithImageData : public Texture2DOpenGL3 {
public:
    Texture2DOpenGL3WithImageData(const core::Image &image, TextureTarget target, bool generateMipMaps);

    void bind() const override;

private:
    core::Image image_;
    mutable bool uploaded_{false};
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr