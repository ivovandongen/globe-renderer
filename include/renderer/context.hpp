#pragma once

namespace renderer {

class Context {
public:
    virtual ~Context() = default;

    virtual void makeCurrent() const = 0;

    virtual void clear() = 0;

    virtual void draw() = 0;
};

} // namespace renderer