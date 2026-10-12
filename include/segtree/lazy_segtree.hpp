#pragma once
#include <vector>

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct LazySegmentTree {
    int n, size, log;
    std::vector<S> data;
    std::vector<F> lazy;

    LazySegmentTree() : LazySegmentTree(0) {}
    explicit LazySegmentTree(int n) : LazySegmentTree(std::vector<S>(n, e())) {}
    LazySegmentTree(int n, S x) : LazySegmentTree(std::vector<S>(n, x)) {}
    explicit LazySegmentTree(const std::vector<S>& v) : n((int)v.size()), size(1), log(0) {
        while (size < n) {
            size <<= 1;
            ++log;
        }
        data.assign(size * 2, e());
        lazy.assign(size, id());
        for (int i = 0; i < n; ++i) {
            data[size + i] = v[i];
        }
        for (int i = size - 1; i >= 1; --i) {
            update(i);
        }
    }

    void set(int i, S x) {
        i += size;
        for (int h = log; h >= 1; --h) {
            push(i >> h);
        }
        data[i] = x;
        for (int h = 1; h <= log; ++h) {
            update(i >> h);
        }
    }

    S get(int i) {
        i += size;
        for (int h = log; h >= 1; --h) {
            push(i >> h);
        }
        return data[i];
    }

    S operator[](int i) { return get(i); }

    // [l, r)
    S query(int l, int r) {
        if (l >= r) return e();
        l += size;
        r += size;
        for (int h = log; h >= 1; --h) {
            if (((l >> h) << h) != l) {
                push(l >> h);
            }
            if (((r >> h) << h) != r) {
                push((r - 1) >> h);
            }
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) {
                sml = op(sml, data[l++]);
            }
            if (r & 1) {
                smr = op(data[--r], smr);
            }
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_query() const { return data[1]; }

    void apply(int i, F f) {
        i += size;
        for (int h = log; h >= 1; --h) {
            push(i >> h);
        }
        data[i] = mapping(f, data[i]);
        for (int h = 1; h <= log; ++h) {
            update(i >> h);
        }
    }

    // [l, r)
    void apply(int l, int r, F f) {
        if (l >= r) return;
        l += size;
        r += size;
        for (int h = log; h >= 1; --h) {
            if (((l >> h) << h) != l) {
                push(l >> h);
            }
            if (((r >> h) << h) != r) {
                push((r - 1) >> h);
            }
        }

        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) {
                all_apply(l++, f);
            }
            if (r & 1) {
                all_apply(--r, f);
            }
            l >>= 1;
            r >>= 1;
        }
        l = l2;
        r = r2;

        // 区間をまたぐ祖先だけ再計算し、遅延作用を持つノードを保つ。
        for (int h = 1; h <= log; ++h) {
            if (((l >> h) << h) != l) {
                update(l >> h);
            }
            if (((r >> h) << h) != r) {
                update((r - 1) >> h);
            }
        }
    }

  private:
    void update(int k) { data[k] = op(data[k << 1 | 0], data[k << 1 | 1]); }

    void all_apply(int k, F f) {
        data[k] = mapping(f, data[k]);
        // 既存の作用の後に f を適用する。
        if (k < size) {
            lazy[k] = composition(f, lazy[k]);
        }
    }

    void push(int k) {
        all_apply(k << 1 | 0, lazy[k]);
        all_apply(k << 1 | 1, lazy[k]);
        lazy[k] = id();
    }
};
