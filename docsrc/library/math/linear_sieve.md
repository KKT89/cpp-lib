# 線形篩

線形篩 (Linear Sieve) により、$N$ 以下の各整数の最小素因数と素数リストを求めます。

## Interface

```cpp
LinearSieve<N> sieve;          // N 以下を篩にかける, O(N)
int p = sieve.lp[i];           // i の最小素因数
int cnt = sieve.prime_cnt;     // N 以下の素数の個数
int prime = sieve.primes[k];   // k 番目の素数
```

## Notes

- `lp[0] = lp[1] = -1` です。
- `lp[i] == i` なら `i` は素数です。
- 配列を大きく持つため、大きい `N` ではグローバルに置くのが安全です。
