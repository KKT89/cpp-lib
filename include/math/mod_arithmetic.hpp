#pragma once
#include <cassert>
#include <cstdint>

constexpr std::uint64_t mod_mul(std::uint64_t a, std::uint64_t b, std::uint64_t mod) {
    assert(mod >= 1);
    return (std::uint64_t)((__uint128_t)a * b % mod);
}

constexpr std::uint64_t mod_pow(std::uint64_t a, std::uint64_t n, std::uint64_t mod) {
    assert(mod >= 1);
    a %= mod;
    std::uint64_t res = 1 % mod;
    while (n > 0) {
        if (n & 1) {
            res = mod_mul(res, a, mod);
        }
        a = mod_mul(a, a, mod);
        n >>= 1;
    }
    return res;
}
