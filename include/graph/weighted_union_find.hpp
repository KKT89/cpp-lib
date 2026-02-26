#pragma once
#include <numeric>
#include <vector>

// 重み付き Union-Find
// unite(x, y, w): weight(y) - weight(x) = w を課す
template <typename T>
struct WeightedUnionFind {
    std::vector<int> par, sz;
    std::vector<T> ws;

    explicit WeightedUnionFind(int n) : par(n), sz(n, 1), ws(n, T{0}) {
        std::iota(par.begin(), par.end(), 0);
    }

    int find(int x) {
        if (par[x] == x) return x;
        int r = find(par[x]);
        ws[x] += ws[par[x]];
        return par[x] = r;
    }

    T weight(int x) {
        find(x);
        return ws[x];
    }

    bool unite(int x, int y, T w) {
        if (same(x, y)) return diff(x, y) == w;
        w += weight(x), w -= weight(y);
        x = find(x), y = find(y);
        if (sz[x] < sz[y]) {
            std::swap(x, y);
            w = -w;
        }
        par[y] = x;
        sz[x] += sz[y];
        ws[y] = w;
        return true;
    }

    bool same(int x, int y) { return find(x) == find(y); }
    T diff(int x, int y) { return weight(y) - weight(x); }
    int size(int x) { return sz[find(x)]; }
};
