#pragma once
#include <vector>

template <class S, S (*op)(S, S), S (*e)(), int POOL_SIZE = 20000000>
struct persistent_segtree {
    struct node {
        S data;
        int l, r;
    };

    int n;
    std::vector<node> pool;
    std::vector<int> roots;

    persistent_segtree() : persistent_segtree(0) {}

    explicit persistent_segtree(int n) : n(n) {
        pool.reserve(POOL_SIZE);
        pool.push_back({e(), 0, 0});
        roots.push_back(0);
    }

    explicit persistent_segtree(const std::vector<S> &v) : persistent_segtree((int)v.size()) {
        if (n > 0) roots[0] = build(0, n, v);
    }

    // [l, r)
    S query(int root_id, int l, int r) {
        return query_(roots[root_id], l, r, 0, n);
    }

    S get(int root_id, int k) { return query(root_id, k, k + 1); }

    int set(int k, S x, int root_id = -1) {
        root_id = resolve(root_id);
        roots.push_back(set_(k, x, roots[root_id], 0, n));
        return (int)roots.size() - 1;
    }

    int apply(int k, S x, int root_id = -1) {
        root_id = resolve(root_id);
        roots.push_back(apply_(k, x, roots[root_id], 0, n));
        return (int)roots.size() - 1;
    }

    int version_count() const { return (int)roots.size(); }

  private:
    int resolve(int id) {
        return id < 0 ? (int)roots.size() - 1 : id;
    }

    int new_node(S data) {
        pool.push_back({data, 0, 0});
        return (int)pool.size() - 1;
    }

    int pull(int l, int r) {
        pool.push_back({op(pool[l].data, pool[r].data), l, r});
        return (int)pool.size() - 1;
    }

    int build(int l, int r, const std::vector<S> &v) {
        if (l + 1 == r) return new_node(v[l]);
        int m = (l + r) >> 1;
        return pull(build(l, m, v), build(m, r, v));
    }

    int set_(int k, S x, int nd, int l, int r) {
        if (l + 1 == r) return new_node(x);
        int m = (l + r) >> 1;
        if (k < m) return pull(set_(k, x, pool[nd].l, l, m), pool[nd].r);
        return pull(pool[nd].l, set_(k, x, pool[nd].r, m, r));
    }

    int apply_(int k, S x, int nd, int l, int r) {
        if (l + 1 == r) return new_node(op(x, pool[nd].data));
        int m = (l + r) >> 1;
        if (k < m) return pull(apply_(k, x, pool[nd].l, l, m), pool[nd].r);
        return pull(pool[nd].l, apply_(k, x, pool[nd].r, m, r));
    }

    S query_(int nd, int a, int b, int l, int r) {
        if (r <= a || b <= l) return e();
        if (a <= l && r <= b) return pool[nd].data;
        int m = (l + r) >> 1;
        return op(query_(pool[nd].l, a, b, l, m), query_(pool[nd].r, a, b, m, r));
    }
};
