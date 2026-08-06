#pragma once
#include "segtree/segtree.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

// 可換モノイド上の一点更新・二次元矩形積を処理する領域木
template <class S, S (*op)(S, S), S (*e)(), class T>
class RangeTree {
    using Point = std::pair<T, T>;

    int n = 0;
    bool built = false;
    std::vector<Point> points;
    // 各ノードに含まれる点を (y, x) 順に保持する
    std::vector<std::vector<Point>> range_points;
    std::vector<SegmentTree<S, op, e>> segtrees;

    int point_index(T x, T y) const {
        auto it = std::lower_bound(points.begin(), points.end(), Point{x, y});
        assert(it != points.end() && *it == Point(x, y));
        return (int)std::distance(points.begin(), it);
    }

    int inner_index(int v, T x, T y) const {
        auto it = std::lower_bound(range_points[v].begin(), range_points[v].end(), Point{y, x});
        assert(it != range_points[v].end() && *it == Point(y, x));
        return (int)std::distance(range_points[v].begin(), it);
    }

    S inner_prod(int v, T yl, T yr) const {
        auto first = range_points[v].begin();
        auto last = range_points[v].end();
        auto compare_y = [](const Point& point, const T& y) { return point.first < y; };
        int l = (int)std::distance(first, std::lower_bound(first, last, yl, compare_y));
        int r = (int)std::distance(first, std::lower_bound(first, last, yr, compare_y));
        return segtrees[v].query(l, r);
    }

  public:
    RangeTree() = default;

    void add_point(T x, T y) {
        assert(!built);
        points.emplace_back(x, y);
    }

    // O(N log N) 
    void build() {
        assert(!built);
        std::sort(points.begin(), points.end());
        points.erase(std::unique(points.begin(), points.end()), points.end());
        n = (int)points.size();

        range_points.resize(n * 2);
        for (int i = 0; i < n; ++i) {
            range_points[n + i] = {{points[i].second, points[i].first}};
        }
        for (int i = n - 1; i >= 1; --i) {
            const auto& left = range_points[i << 1 | 0];
            const auto& right = range_points[i << 1 | 1];
            std::merge(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(range_points[i]));
        }

        segtrees.reserve(n * 2);
        for (const auto& node_points : range_points) {
            segtrees.emplace_back((int)node_points.size());
        }
        built = true;
    }

    // O(log^2 N)
    void set(T x, T y, S value) {
        assert(built);
        int i = point_index(x, y) + n;
        while (i >= 1) {
            segtrees[i].set(inner_index(i, x, y), value);
            i >>= 1;
        }
    }

    // O(log^2 N)
    void add(T x, T y, S value) {
        assert(built);
        int i = point_index(x, y) + n;
        while (i >= 1) {
            int j = inner_index(i, x, y);
            segtrees[i].set(j, op(segtrees[i][j], value));
            i >>= 1;
        }
    }

    // [xl, xr) x [yl, yr), O(log^2 N)
    S prod(T xl, T xr, T yl, T yr) const {
        assert(built);
        assert(!(xr < xl) && !(yr < yl));
        auto compare_x = [](const Point& point, const T& x) { return point.first < x; };
        int l = n + (int)std::distance(points.begin(), std::lower_bound(points.begin(), points.end(), xl, compare_x));
        int r = n + (int)std::distance(points.begin(), std::lower_bound(points.begin(), points.end(), xr, compare_x));
        S result = e();
        while (l < r) {
            if (l & 1) result = op(result, inner_prod(l++, yl, yr));
            if (r & 1) result = op(result, inner_prod(--r, yl, yr));
            l >>= 1;
            r >>= 1;
        }
        return result;
    }

    // O(log N)
    S get(T x, T y) const {
        assert(built);
        point_index(x, y);
        return segtrees[1][inner_index(1, x, y)];
    }
};
