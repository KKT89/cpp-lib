#pragma once
#include <vector>

#include "data_structure/dual_segtree.hpp"

namespace range_affine_point_get_internal {
template <class T>
struct Affine {
    T a, b;
};

template <class T>
T e() {
    return T();
}

template <class T>
T mapping(Affine<T> f, T x) {
    return f.a * x + f.b;
}

// g の後に f を適用する
template <class T>
Affine<T> composition(Affine<T> f, Affine<T> g) {
    return {f.a * g.a, f.a * g.b + f.b};
}

template <class T>
Affine<T> id() {
    return {T(1), T()};
}

template <class T>
using base = DualSegmentTree<T, e<T>, Affine<T>, mapping<T>, composition<T>, id<T>>;
} // namespace range_affine_point_get_internal

template <class T>
struct RangeAffinePointGet : range_affine_point_get_internal::base<T> {
    using Base = range_affine_point_get_internal::base<T>;

    RangeAffinePointGet() : Base() {}
    explicit RangeAffinePointGet(int n) : Base(n) {}
    RangeAffinePointGet(int n, T x) : Base(n, x) {}
    explicit RangeAffinePointGet(const std::vector<T>& v) : Base(v) {}

    void apply(int l, int r, T a, T b) { Base::apply(l, r, {a, b}); }
};
