#pragma once

namespace glbr {
namespace core {

template <class T>
struct Size2D {
    T width;
    T height;
};

template <class T>
struct Size3D {
    T width;
    T height;
    T depth;
};

}  // namespace core
}  // namespace glbr