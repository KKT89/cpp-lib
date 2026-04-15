#pragma once
#include <cassert>
#include <utility>
#include <vector>

// 中国剰余定理 (拡張: 法が互いに素でなくても可)
// crt(r, m): x ≡ r[i] (mod m[i]) を満たす (最小非負 x, lcm) を返す
// 解なし → {0, 0}, 空入力 → {0, 1}
// 制約: m[i] >= 1, 答えの lcm が long long に収まること
std::pair<long long, long long> crt(const std::vector<long long>& r, const std::vector<long long>& m) {
    assert(r.size() == m.size());
    int n = (int)r.size();
    long long r0 = 0, m0 = 1;
    for (int i = 0; i < n; i++) {
        assert(m[i] >= 1);
        long long r1 = r[i] % m[i];
        if (r1 < 0) r1 += m[i];
        long long m1 = m[i];
        if (m0 < m1) {
            std::swap(r0, r1);
            std::swap(m0, m1);
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }
        // m0 * im ≡ g (mod m1) を満たす (g, im) を求める (g = gcd(m0, m1))
        long long g, im;
        {
            long long a = m0 % m1, s = m1, t = a;
            long long x0 = 0, x1 = 1;
            while (t) {
                long long u = s / t;
                s -= t * u;
                x0 -= x1 * u;
                std::swap(s, t);
                std::swap(x0, x1);
            }
            g = s;
            im = x0;
            if (im < 0) im += m1 / g;
        }
        if ((r1 - r0) % g != 0) return {0, 0};
        long long u1 = m1 / g;
        long long x = (long long)((__int128)(r1 - r0) / g % u1 * im % u1);
        r0 += x * m0;
        m0 *= u1;
        if (r0 < 0) r0 += m0;
    }
    return {r0, m0};
}
