#pragma once

#include <renderer/context.hpp>
#include <renderer/graphics_window.hpp>

namespace renderer {
namespace opengl3 {

class ContextOpenGL3 : public Context {
public:
    ContextOpenGL3(const GraphicsWindow &);

    ~ContextOpenGL3() override = default;

    void makeCurrent() const override;

    void clear() override;

    void draw() override;

private:
    const GraphicsWindow &_window;
};

} // namespace opengl3
} // namespace renderer