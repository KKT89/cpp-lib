#pragma once
#include <vector>

#include "data_structure/dual_segtree.hpp"

namespace range_add_point_get_internal {
template <class T>
T e() {
    return T();
}

template <class T>
T mapping(T f, T x) {
    return x + f;
}

template <class T>
T composition(T f, T g) {
    return f + g;
}

template <class T>
T id() {
    return T();
}

template <class T>
using base = DualSegmentTree<T, e<T>, T, mapping<T>, composition<T>, id<T>>;
} // namespace range_add_point_get_internal

template <class T>
struct RangeAddPointGet : range_add_point_get_internal::base<T> {
    using Base = range_add_point_get_internal::base<T>;

    RangeAddPointGet() : Base() {}
    explicit RangeAddPointGet(int n) : Base(n) {}
    RangeAddPointGet(int n, T x) : Base(n, x) {}
    explicit RangeAddPointGet(const std::vector<T>& v) : Base(v) {}

    void add(int l, int r, T x) { this->apply(l, r, x); }
};
