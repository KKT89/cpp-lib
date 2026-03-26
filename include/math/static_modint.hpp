#pragma once
#include <cstdint>
#include <iostream>

template <int mod>
struct static_modint {
    using mint = static_modint;
    using u32 = unsigned int;
    using u64 = std::uint64_t;

    static_assert(1 <= mod);

    u32 x;

    static_modint() : x(0) {}
    static_modint(std::int64_t y) {
        std::int64_t z = y % mod;
        if (z < 0) z += mod;
        x = (u32)z;
    }

    static constexpr int get_mod() { return mod; }
    static constexpr u32 umod() { return (u32)mod; }
    int val() const { return (int)x; }

    mint& operator+=(const mint& rhs) {
        if ((x += rhs.x) >= umod()) x -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        if ((x += umod() - rhs.x) >= umod()) x -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        x = (u32)((u64)x * rhs.x % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this *= rhs.inv(); }

    mint pow(long long n) const {
        mint a = *this, r = 1;
        while (n > 0) {
            if (n & 1) r *= a;
            a *= a;
            n >>= 1;
        }
        return r;
    }
    mint inv() const { return pow(mod - 2); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs; }
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs; }
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs; }
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs; }
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs.x == rhs.x; }
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs.x != rhs.x; }

    friend std::ostream& operator<<(std::ostream& os, const mint& p) { return os << p.x; }
    friend std::istream& operator>>(std::istream& is, mint& a) {
        std::int64_t t;
        is >> t;
        a = mint(t);
        return is;
    }
};
