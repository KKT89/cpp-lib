#pragma once
#include <cassert>
#include <utility>
#include <vector>

// primes: 素数リスト, lp[i]: i の最小素因数 (0, 1 の最小素因数は -1)
// 構築: O(n) 時間・領域, 素因数分解: O(log(x + 1))
struct LinearSieve {
    std::vector<long long> lp, primes;

    explicit LinearSieve(long long n) {
        assert(n >= 0);
        lp.resize(n + 1);
        lp[0] = -1;
        if (n >= 1) {
            lp[1] = -1;
        }
        for (long long i = 2; i <= n; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }
            long long limit = n / i;
            for (long long p : primes) {
                if (p > lp[i] || p > limit) break;
                lp[i * p] = p;
            }
        }
    }

    bool isprime(long long i) const {
        assert(0 <= i && i < (long long)lp.size());
        return lp[i] == i;
    }

    std::vector<std::pair<long long, int>> factorize(long long x) const {
        assert(1 <= x && x < (long long)lp.size());
        std::vector<std::pair<long long, int>> res;
        while (x > 1) {
            long long p = lp[x];
            int e = 0;
            do {
                x /= p;
                e++;
            } while (x > 1 && lp[x] == p);
            res.emplace_back(p, e);
        }
        return res;
    }
};
