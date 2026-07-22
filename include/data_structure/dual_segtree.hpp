#pragma once
#include <vector>

template <class S, S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct dual_segtree {
    int n, size, log;
    std::vector<S> data;
    std::vector<F> lazy;

    dual_segtree() : dual_segtree(0) {}
    explicit dual_segtree(int n) : dual_segtree(n, e()) {}
    dual_segtree(int n, S x) { init(n, x); }
    explicit dual_segtree(const std::vector<S>& v) {
        init((int)v.size(), e());
        for (int i = 0; i < n; i += 1) {
            data[i] = v[i];
        }
    }

    void set(int i, S x) {
        i += size;
        for (int h = log; h >= 1; h -= 1) {
            push(i >> h);
        }
        data[i - size] = x;
    }

    S get(int i) {
        i += size;
        for (int h = log; h >= 1; h -= 1) {
            push(i >> h);
        }
        return data[i - size];
    }

    S operator[](int i) { return get(i); }

    // [l, r)
    void apply(int l, int r, F f) {
        if (l >= r) return;

        l += size;
        r += size;

        for (int h = log; h >= 1; h -= 1) {
            if (((l >> h) << h) != l) {
                push(l >> h);
            }
            if (((r >> h) << h) != r) {
                push((r - 1) >> h);
            }
        }

        while (l < r) {
            if (l & 1) {
                all_apply(l, f);
                l += 1;
            }
            if (r & 1) {
                r -= 1;
                all_apply(r, f);
            }
            l >>= 1;
            r >>= 1;
        }
    }

  private:
    void init(int m, S x) {
        n = m;
        size = 1;
        log = 0;
        while (size < n) {
            size <<= 1;
            log += 1;
        }
        data.assign(size, x);
        lazy.assign(size, id());
    }

    void all_apply(int k, F f) {
        if (k < size) {
            lazy[k] = composition(f, lazy[k]);
        } else {
            data[k - size] = mapping(f, data[k - size]);
        }
    }

    void push(int k) {
        all_apply(k << 1 | 0, lazy[k]);
        all_apply(k << 1 | 1, lazy[k]);
        lazy[k] = id();
    }
};
