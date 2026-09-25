#pragma once
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <map>
#include <numeric>
#include <random>
#include <utility>
#include <vector>

#include "math/is_prime.hpp"
#include "math/mod_arithmetic.hpp"

namespace factorize {

using u64 = std::uint64_t;
using u128 = __uint128_t;
using ::is_prime;
using ::mod_mul;
using ::mod_pow;

inline std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

u64 binary_gcd(u64 a, u64 b) {
    if (a == 0) return b;
    if (b == 0) return a;
    int shift = __builtin_ctzll(a | b);
    a >>= __builtin_ctzll(a);
    while (b > 0) {
        b >>= __builtin_ctzll(b);
        if (a > b) std::swap(a, b);
        b -= a;
    }
    return a << shift;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;

    while (true) {
        u64 c = std::uniform_int_distribution<u64>(1, n - 1)(rng);
        u64 y = std::uniform_int_distribution<u64>(0, n - 1)(rng);
        u64 r = 1, q = 1, g = 1, x = 0, ys = 0;
        constexpr u64 batch = 128;

        auto f = [&](u64 v) { return (mod_mul(v, v, n) + c) % n; };

        while (g == 1) {
            x = y;
            for (u64 i = 0; i < r; i++) {
                y = f(y);
            }
            for (u64 k = 0; k < r && g == 1; k += batch) {
                ys = y;
                for (u64 i = 0; i < std::min(batch, r - k); i++) {
                    y = f(y);
                    q = mod_mul(q, x > y ? x - y : y - x, n);
                }
                g = binary_gcd(q, n);
            }
            r <<= 1;
        }

        if (g == n) {
            do {
                ys = f(ys);
                g = binary_gcd(x > ys ? x - ys : ys - x, n);
            } while (g == 1);
        }
        if (g != n) return g;
    }
}

void prime_factor_dfs(u64 n, std::vector<u64>& res) {
    if (n == 1) return;
    if (is_prime(n)) {
        res.push_back(n);
        return;
    }
    u64 p = pollard_rho(n);
    prime_factor_dfs(p, res);
    prime_factor_dfs(n / p, res);
}

template <typename T>
std::vector<T> prime_factor(T n) {
    std::vector<u64> tmp;
    prime_factor_dfs((u64)n, tmp);
    std::sort(tmp.begin(), tmp.end());

    std::vector<T> res;
    res.reserve(tmp.size());
    for (u64 p : tmp) {
        res.push_back((T)p);
    }
    return res;
}

template <typename T>
std::map<T, int> factor_count(T n) {
    std::map<T, int> res;
    for (T p : prime_factor(n)) {
        res[p]++;
    }
    return res;
}

template <typename T>
std::vector<T> divisors(T n) {
    if (n == 0) return {};
    std::vector<std::pair<T, int>> factors;
    for (auto p : factor_count(n)) {
        factors.push_back(p);
    }

    std::vector<T> res;
    auto dfs = [&](auto self, int i, T x) -> void {
        if (i == (int)factors.size()) {
            res.push_back(x);
            return;
        }
        for (int j = 0; j <= factors[i].second; j++) {
            self(self, i + 1, x);
            if (j + 1 <= factors[i].second) x *= factors[i].first;
        }
    };
    dfs(dfs, 0, 1);
    std::sort(res.begin(), res.end());
    return res;
}

} // namespace factorize
