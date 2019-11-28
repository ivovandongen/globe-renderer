#pragma once

namespace glbr {
namespace core {
namespace geometry {

template <class T>
class Point2D {
public:
    Point2D(T x, T y) : x_(x), y_(y) {}

    inline T x() const { return x_; };
    inline T y() const { return y_; };

private:
    T x_;
    T y_;
};

template <class T>
inline bool operator==(const Point2D<T>& lhs, const Point2D<T>& rhs) {
    return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

template <class T>
inline Point2D<T> operator/(const Point2D<T>& lhs, int rhs) {
    return {lhs.x() / rhs, lhs.y() / rhs};
}

}  // namespace geometry
}  // namespace core
}  // namespace glbr