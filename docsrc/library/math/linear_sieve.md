# 線形篩

線形篩 (Linear Sieve) により、$n$ 以下の各整数の最小素因数と素数リストを $O(n)$ で求めます。

## Interface

```cpp
LinearSieve<N> sieve;          // N 以下を篩にかける (グローバルに置く)
sieve.primes[0..prime_cnt)     // N 以下の素数リスト
sieve.prime_cnt                // 素数の個数
sieve.lp[i]                    // i の最小素因数 (lp[0] = lp[1] = -1)
```

| 操作 | 計算量 |
|------|--------|
| `LinearSieve<N>()` | $O(N)$ |

## Code

```cpp
--8<-- "include/math/linear_sieve.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/linear_sieve.hpp"
```
