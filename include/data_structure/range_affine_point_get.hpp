#pragma once
#include <vector>

#include "data_structure/dual_segtree.hpp"

namespace range_affine_point_get_internal {
template <class T>
struct affine {
    T a, b;
};

template <class T>
T e() {
    return T();
}

template <class T>
T mapping(affine<T> f, T x) {
    return f.a * x + f.b;
}

// g の後に f を適用する
template <class T>
affine<T> composition(affine<T> f, affine<T> g) {
    return {f.a * g.a, f.a * g.b + f.b};
}

template <class T>
affine<T> id() {
    return {T(1), T()};
}

template <class T>
using base = dual_segtree<T, e<T>, affine<T>, mapping<T>, composition<T>, id<T>>;
} // namespace range_affine_point_get_internal

template <class T>
struct range_affine_point_get : range_affine_point_get_internal::base<T> {
    using Base = range_affine_point_get_internal::base<T>;

    range_affine_point_get() : Base() {}
    explicit range_affine_point_get(int n) : Base(n) {}
    range_affine_point_get(int n, T x) : Base(n, x) {}
    explicit range_affine_point_get(const std::vector<T>& v) : Base(v) {}

    void apply(int l, int r, T a, T b) { Base::apply(l, r, {a, b}); }
};
