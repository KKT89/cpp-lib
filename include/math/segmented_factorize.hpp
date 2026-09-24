#pragma once
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

#include "math/linear_sieve.hpp"

// [L, R] を分解し、res[i] に L + i の (素因数, 指数) を昇順で返す。1 は空。
// 計算量: O(sqrt(R) + W log(R + 1)), W = R - L + 1
inline std::vector<std::vector<std::pair<long long, int>>> segmented_factorize(long long L, long long R) {
    assert(1 <= L && L <= R);

    long long n = (long long)std::sqrt((long double)R);
    while (n + 1 <= R / (n + 1)) {
        n++;
    }
    while (n > R / n) {
        n--;
    }

    LinearSieve sieve(n);

    long long w = R - L + 1;
    std::vector<long long> rem(w);
    std::vector<std::vector<std::pair<long long, int>>> res(w);
    for (long long i = 0; i < w; i++) {
        rem[i] = L + i;
    }

    for (long long p : sieve.primes) {
        for (long long i = (p - L % p) % p; i < w;) {
            int e = 0;
            while (rem[i] % p == 0) {
                rem[i] /= p;
                e++;
            }
            res[i].emplace_back(p, e);
            if (w - 1 - i < p) break;
            i += p;
        }
    }
    for (long long i = 0; i < w; i++) {
        if (rem[i] > 1) {
            res[i].emplace_back(rem[i], 1);
        }
    }
    return res;
}
