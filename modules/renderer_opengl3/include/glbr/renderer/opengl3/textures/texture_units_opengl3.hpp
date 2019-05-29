#pragma once

#include <glbr/renderer/textures/texture_units.hpp>
#include "texture_unit_opengl3.hpp"

#include <vector>

namespace glbr {
namespace renderer {
namespace opengl3 {

class TextureUnitsOpenGL3 : public TextureUnits {
public:
    TextureUnitsOpenGL3();
    ~TextureUnitsOpenGL3() override;

    TextureUnit& operator[](int i) override;

    void clean();
private:
    std::vector<TextureUnitOpenGL3> _units;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr