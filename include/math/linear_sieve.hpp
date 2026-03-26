#pragma once

// 線形篩
// primes[0..prime_cnt): 素数リスト, lp[i]: i の最小素因数 (lp[0] = lp[1] = -1)
template <int N>
struct LinearSieve {
    int lp[N + 1]{};
    int primes[N]{};
    int prime_cnt = 0;

    LinearSieve() {
        lp[0] = lp[1] = -1;
        for (int i = 2; i <= N; i++) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes[prime_cnt] = i;
                prime_cnt += 1;
            }
            for (int j = 0; j < prime_cnt && primes[j] <= lp[i] && (long long)i * primes[j] <= N; j++) {
                lp[i * primes[j]] = primes[j];
            }
        }
    }
};
