# 高速素因数分解

Miller-Rabin と Pollard Rho による 64bit 整数の素数判定・素因数分解です。

## Interface

```cpp
bool ok = factorize::is_prime(n);

vector<long long> ps = factorize::prime_factor(n);     // 素因数を昇順で列挙
map<long long, int> mp = factorize::factor_count(n);   // 素因数ごとの指数
vector<long long> ds = factorize::divisors(n);         // 約数を昇順で列挙
```

## Notes

- 素因数分解は $n \ge 1$、`divisors(n)` は $n \ge 0$ を仮定します。
- $n=1$ の素因数分解は空、約数は `{1}` です。`divisors(0)` は空を返します。
