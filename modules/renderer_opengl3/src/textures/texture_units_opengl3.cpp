#include <glbr/renderer/opengl3/textures/texture_units_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/context/context_opengl3.hpp>
#include <glbr/renderer/opengl3/errors.hpp>
#include <glbr/renderer/opengl3/textures/texture_unit_opengl3.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

TextureUnitsOpenGL3::TextureUnitsOpenGL3() {
    int texture_units;
    GL_VERIFY(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units));
    logging::debug("Preparing {} texture units", texture_units);

    units_.reserve(texture_units);
    for (int i = 0; i < texture_units; i++) {
        units_.emplace_back(i);
    }
};

TextureUnitsOpenGL3::~TextureUnitsOpenGL3() = default;

TextureUnit& TextureUnitsOpenGL3::operator[](int i) {
    assert(i < units_.size());
    return units_[i];
}

void TextureUnitsOpenGL3::clean(ContextOpenGL3& context) {
    for (auto& unit : units_) {
        unit.clean(context);
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr