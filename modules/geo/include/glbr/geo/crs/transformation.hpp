#pragma once

namespace glbr {
namespace geo {
namespace crs {

template <class T>
class Transformation {
public:
    Transformation(T a, T b, T c, T d) : a_(a), b_(b), c_(c), d_(d) {}

    core::geometry::Point2D<T> transform(const core::geometry::Point2D<T>& input, T scale) const {
        return {scale * (a_ * input.x() + b_), scale * (c_ * input.y() + d_)};
    }

    core::geometry::Point2D<T> untransform(core::geometry::Point2D<T> input, T scale) const {
        return core::geometry::Point2D<T>{(input.x() / scale - b_) / a_, (input.y() / scale - d_) / c_};
    }

private:
    T a_, b_, c_, d_;
};

}  // namespace crs
}  // namespace geo
}  // namespace glbr
