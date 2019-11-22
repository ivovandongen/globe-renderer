#pragma once

#include "point_2d.hpp"

namespace glbr {
namespace core {
namespace geometry {

template <class T>
class Point3D {
public:
    Point3D(T x, T y, T z) : x_(x), y_(y), z_(z) {}
    explicit Point3D(const Point2D<T>& p) : x_(p.x()), y_(p.y()), z_(0) {}

    inline T x() const { return x_; };
    inline T y() const { return y_; };
    inline T z() const { return z_; };

    inline T& x() { return x_; };
    inline T& y() { return y_; };
    inline T& z() { return z_; };

    explicit operator Point2D<T>() { return {x_, y_}; }

private:
    T x_;
    T y_;
    T z_;
};

template <class T>
inline bool operator==(const Point3D<T>& lhs, const Point3D<T>& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

}  // namespace geometry
}  // namespace core
}  // namespace glbr