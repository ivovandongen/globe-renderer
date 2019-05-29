#include <glbr/renderer/opengl3/textures/texture_units_opengl3.hpp>

#include <glbr/logging/logging.hpp>
#include <glbr/renderer/opengl3/errors.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

TextureUnitsOpenGL3::TextureUnitsOpenGL3() {
    int texture_units;
    GL_VERIFY(glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_units));
    logging::debug("Preparing {} texture units", texture_units);

    _units.reserve(texture_units);
    for (int i = 0; i < texture_units; i++) {
        _units.emplace_back(i);
    }
};

TextureUnitsOpenGL3::~TextureUnitsOpenGL3() = default;

TextureUnit& TextureUnitsOpenGL3::operator[](int i) {
    assert(i < _units.size());
    return _units[i];
}
void TextureUnitsOpenGL3::clean() {
    for (auto& unit : _units) {
        unit.clean();
    }
}

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr