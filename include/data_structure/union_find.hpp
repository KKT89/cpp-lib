#pragma once
#include <numeric>
#include <vector>

struct UnionFind {
    std::vector<int> par, num;
    UnionFind(int n) : par(n), num(n, 1) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int v) {
        return (par[v] == v) ? v : (par[v] = find(par[v]));
    }
    void unite(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (num[u] < num[v]) std::swap(u, v);
        num[u] += num[v];
        par[v] = u;
    }
    bool same(int u, int v) {
        return find(u) == find(v);
    }
    int size(int v) {
        return num[find(v)];
    }
};
