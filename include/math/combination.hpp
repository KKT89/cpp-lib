#pragma once
#include <vector>

// 二項係数 (mod 素数, n < mod): 階乗テーブルを自動拡張
template <typename T, int N = 0>
struct Combination {
    std::vector<T> p, invp;

    Combination() : p(1, T(1)), invp(1, T(1)) { if constexpr (N > 0) extend(N); }

    void extend(long long n) {
        long long m = (long long)T::get_mod() - 1;
        if (m >= 0 && n > m) n = m; // n! が 0 にならない範囲に制限
        if (n < (long long)p.size()) return;
        long long old_sz = p.size();
        p.resize(n + 1);
        invp.resize(n + 1);
        for (long long i = old_sz; i <= n; ++i) {
            p[i] = p[i - 1] * i;
        }
        invp[n] = p[n].inv();
        for (long long i = n - 1; i >= old_sz; --i) {
            invp[i] = invp[i + 1] * (i + 1);
        }
    }

    T comb(long long n, long long r) {
        if (r < 0 || n < r) return 0;
        if (n >= (long long)T::get_mod()) return 0;
        extend(n);
        return p[n] * invp[n - r] * invp[r];
    }

    T big_comb(T n, long long r) {
        if (r < 0) return 0;
        if (r >= (long long)T::get_mod()) return 0;
        extend(r);
        T res = invp[r];
        for (long long i = 0; i < r; ++i) {
            res *= (n - i);
        }
        return res;
    }

    // Lucas の定理: n >= mod でも正しく計算 (mod は素数)
    T lucas(long long n, long long r) {
        if (r < 0 || n < r) return 0;
        long long m = T::get_mod();
        T res = 1;
        while (n > 0) {
            long long ni = n % m, ri = r % m;
            if (ni < ri) return 0;
            res *= comb(ni, ri);
            n /= m;
            r /= m;
        }
        return res;
    }
};
