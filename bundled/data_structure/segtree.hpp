// bundled by scripts/bundle_header.py

// ---- begin: include/data_structure/segtree.hpp
#include <vector>

template <class S, S (*op)(S, S), S (*e)()> struct segtree {
    int n;
    std::vector<S> tree;
    segtree() : segtree(0) {}
    explicit segtree(int n) : n(n), tree(vector<S>(n << 1, e())) {}
    explicit segtree(const std::vector<S> &v) : n((int)v.size()) {
        tree.resize(n * 2);
        for (int i = 0; i < n; ++i) {
            tree[n + i] = v[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            update(i);
        }
    }
    void update(int k) { tree[k] = op(tree[k << 1 | 0], tree[k << 1 | 1]); }
    S operator[](int i) { return tree[i + n]; }
    void set(int i, S x) {
        i += n;
        tree[i] = x;
        while (i >>= 1) {
            update(i);
        }
    }
    // [l,r)
    S query(int l, int r) {
        S sml = e(), smr = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = op(sml, tree[l++]);
            if (r & 1) smr = op(tree[--r], smr);
        }
        return op(sml, smr);
    }
};
// ---- end: include/data_structure/segtree.hpp
