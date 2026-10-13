#pragma once
#include <algorithm>
#include <limits>
#include <vector>

#include "segtree/lazy_segtree.hpp"

namespace range_add_range_min_internal {
template <class T>
T op(T x, T y) {
    return std::min(x, y);
}

template <class T>
T e() {
    return std::numeric_limits<T>::max();
}

template <class T>
T mapping(T f, T x) {
    // max() は空区間の単位元として保持する。
    return x == e<T>() ? x : x + f;
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
using base = LazySegmentTree<T, op<T>, e<T>, T, mapping<T>, composition<T>, id<T>>;
} // namespace range_add_range_min_internal

template <class T>
struct RangeAddRangeMin : range_add_range_min_internal::base<T> {
    using Base = range_add_range_min_internal::base<T>;

    RangeAddRangeMin() : Base() {}
    explicit RangeAddRangeMin(int n) : RangeAddRangeMin(n, T()) {}
    RangeAddRangeMin(int n, T x) : Base(n, x) {}
    explicit RangeAddRangeMin(const std::vector<T>& v) : Base(v) {}

    void add(int l, int r, T x) { this->apply(l, r, x); }
};
