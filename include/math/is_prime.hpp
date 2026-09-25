#pragma once
#include <cstdint>
#include <initializer_list>

namespace is_prime_internal {

using u64 = std::uint64_t;
using u128 = __uint128_t;

constexpr u64 mod_mul(u64 a, u64 b, u64 mod) { return (u64)((u128)a * b % mod); }

constexpr u64 mod_pow(u64 a, u64 n, u64 mod) {
    u64 res = 1;
    while (n > 0) {
        if (n & 1) {
            res = mod_mul(res, a, mod);
        }
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}

} // namespace is_prime_internal

// 64bit 非負整数の素数判定。固定した 7 基底の Miller-Rabin を使い、O(log(n + 1)) 時間。
constexpr bool is_prime(std::uint64_t n) {
    using u64 = std::uint64_t;
    using is_prime_internal::mod_mul;
    using is_prime_internal::mod_pow;

    if (n < 2) return false;
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }

    u64 d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}
