#pragma once
#include <vector>

template <class S, S (*op)(S, S), S (*e)()>
struct SegmentTree {
    int n;
    std::vector<S> tree;
    SegmentTree() : SegmentTree(0) {}
    explicit SegmentTree(int n) : n(n), tree(std::vector<S>(n << 1, e())) {}
    explicit SegmentTree(const std::vector<S>& v) : n((int)v.size()) {
        tree.resize(n * 2);
        for (int i = 0; i < n; ++i) {
            tree[n + i] = v[i];
        }
        for (int i = n - 1; i >= 1; --i) {
            update(i);
        }
    }
    void update(int k) { tree[k] = op(tree[k << 1 | 0], tree[k << 1 | 1]); }
    S operator[](int i) const { return tree[i + n]; }
    void set(int i, S x) {
        i += n;
        tree[i] = x;
        while (i >>= 1) {
            update(i);
        }
    }
    // [l,r)
    S query(int l, int r) const {
        S sml = e(), smr = e();
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sml = op(sml, tree[l++]);
            if (r & 1) smr = op(tree[--r], smr);
        }
        return op(sml, smr);
    }

    template <class G>
    int max_right(int l, G f) const {
        if (l == n) return n;
        std::vector<int> nodes, right;
        for (int a = l + n, b = n * 2; a < b; a >>= 1, b >>= 1) {
            if (a & 1) {
                nodes.push_back(a++);
            }
            if (b & 1) {
                right.push_back(--b);
            }
        }
        nodes.insert(nodes.end(), right.rbegin(), right.rend());

        S sm = e();
        for (int k : nodes) {
            S next = op(sm, tree[k]);
            if (f(next)) {
                sm = next;
                continue;
            }
            while (k < n) {
                k <<= 1;
                next = op(sm, tree[k]);
                if (f(next)) {
                    sm = next;
                    ++k;
                }
            }
            return k - n;
        }
        return n;
    }

    template <class G>
    int min_left(int r, G f) const {
        if (r == 0) return 0;
        std::vector<int> nodes, left;
        for (int a = n, b = r + n; a < b; a >>= 1, b >>= 1) {
            if (a & 1) {
                left.push_back(a++);
            }
            if (b & 1) {
                nodes.push_back(--b);
            }
        }
        nodes.insert(nodes.end(), left.rbegin(), left.rend());

        S sm = e();
        for (int k : nodes) {
            S next = op(tree[k], sm);
            if (f(next)) {
                sm = next;
                continue;
            }
            while (k < n) {
                k = k << 1 | 1;
                next = op(tree[k], sm);
                if (f(next)) {
                    sm = next;
                    --k;
                }
            }
            return k - n + 1;
        }
        return 0;
    }
};
