#pragma once

#include <algorithm>

namespace glbr {
namespace core {

template <class T>
T clamp(T in, T min, T max) {
    return std::min(max, std::max(min, in));
}

}  // namespace core
}  // namespace glbr
