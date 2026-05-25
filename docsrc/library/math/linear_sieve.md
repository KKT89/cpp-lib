# 線形篩

線形篩 (Linear Sieve) により、$N$ 以下の各整数の最小素因数と素数リストを求めます。

## Interface

```cpp
LinearSieve<N> sieve;          // N 以下を篩にかける, O(N)
int p = sieve.lp[i];           // i の最小素因数 (lp[0] = lp[1] = -1)
bool b = sieve.isprime(i);     // i が素数なら true
int cnt = sieve.prime_cnt;     // N 以下の素数の個数
int prime = sieve.primes[k];   // k 番目の素数
```
