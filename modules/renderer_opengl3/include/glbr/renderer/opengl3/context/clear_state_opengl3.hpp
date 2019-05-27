#pragma once

#include <glbr/renderer/clear_state.hpp>

namespace glbr {
namespace renderer {
namespace opengl3 {

class ClearStateOpenGL3 {
public:
    ClearStateOpenGL3() = default;

    ClearStateOpenGL3& operator=(const ClearState& update);

private:
    ClearState _clearState;
};

}  // namespace opengl3
}  // namespace renderer
}  // namespace glbr
