# 線形篩

線形篩 (Linear Sieve) により、$n$ 以下の各整数の最小素因数と素数リストを求めます。

## Interface

```cpp
LinearSieve sieve(n);             // n 以下を篩にかける, 時間・領域 O(n)
long long p = sieve.lp[i];        // i の最小素因数
bool b = sieve.isprime(i);        // i が素数なら true, O(1)
auto cnt = sieve.primes.size();   // n 以下の素数の個数
long long q = sieve.primes[k];    // k 番目の素数 (0-indexed)
auto ps = sieve.factorize(x);     // x の (素因数, 指数) を昇順で列挙, O(log(x + 1))
```

## Notes

- $n \ge 0$、`isprime(i)` は $0 \le i \le n$、`factorize(x)` は $1 \le x \le n$ を仮定します。
- `lp`, `primes` は `vector<long long>` です。`lp[0] = -1`、$n \ge 1$ のとき `lp[1] = -1` です。
- `factorize(x)` は `vector<pair<long long, int>>` を返します。$x=1$ の結果は空です。
