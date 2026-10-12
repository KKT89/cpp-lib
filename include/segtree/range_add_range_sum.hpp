#pragma once
#include <vector>

#include "segtree/lazy_segtree.hpp"

namespace range_add_range_sum_internal {
template <class T>
struct Sum {
    T sum;
    int size;
};

template <class T>
Sum<T> op(Sum<T> x, Sum<T> y) {
    return {x.sum + y.sum, x.size + y.size};
}

template <class T>
Sum<T> e() {
    return {T(), 0};
}

template <class T>
Sum<T> mapping(T f, Sum<T> x) {
    return {x.sum + f * T(x.size), x.size};
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
using base = LazySegmentTree<Sum<T>, op<T>, e<T>, T, mapping<T>, composition<T>, id<T>>;

template <class T>
std::vector<Sum<T>> make_data(const std::vector<T>& v) {
    std::vector<Sum<T>> data;
    data.reserve(v.size());
    for (const T& x : v) {
        data.push_back({x, 1});
    }
    return data;
}
} // namespace range_add_range_sum_internal

template <class T>
struct RangeAddRangeSum : range_add_range_sum_internal::base<T> {
    using Base = range_add_range_sum_internal::base<T>;

    RangeAddRangeSum() : Base() {}
    explicit RangeAddRangeSum(int n) : RangeAddRangeSum(n, T()) {}
    // 実葉は長さ 1 で初期化し、余剰葉の長さは 0 のままにする。
    RangeAddRangeSum(int n, T x) : Base(std::vector<range_add_range_sum_internal::Sum<T>>(n, {x, 1})) {}
    explicit RangeAddRangeSum(const std::vector<T>& v) : Base(range_add_range_sum_internal::make_data(v)) {}

    void add(int l, int r, T x) { this->apply(l, r, x); }
    void set(int i, T x) { Base::set(i, {x, 1}); }
    T get(int i) { return Base::get(i).sum; }
    T operator[](int i) { return get(i); }
    T query(int l, int r) { return Base::query(l, r).sum; }
    T all_query() const { return Base::all_query().sum; }
};
