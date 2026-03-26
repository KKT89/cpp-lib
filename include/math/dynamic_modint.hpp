#pragma once
#include <iostream>

// 動的 modint: id を変えることで複数 mod を同時に扱える (mod は素数, mod < 2^63)
template <int id>
struct dynamic_modint {
    using mint = dynamic_modint;
    using u64 = unsigned long long;
    using u128 = __uint128_t;
    inline static u64 mod = 1;

    u64 x;

    static void set_mod(u64 m) { mod = m; }
    static u64 get_mod() { return mod; }

    dynamic_modint() : x(0) {}
    dynamic_modint(long long y) : x(y % (long long)mod + (y < 0 ? mod : 0)) {}

    u64 val() const { return x; }

    mint& operator+=(const mint& rhs) {
        if ((x += rhs.x) >= mod) x -= mod;
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        if (x < rhs.x) x += mod;
        x -= rhs.x;
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        x = (u64)((u128)x * rhs.x % mod);
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
        long long t;
        is >> t;
        a = mint(t);
        return is;
    }
};
