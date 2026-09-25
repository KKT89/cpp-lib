# 素数判定

決定的 Miller-Rabin 法で、64bit 非負整数が素数か判定します。

## Interface

```cpp
bool ok = is_prime(n);   // 素数なら true
```

## Notes

- 引数は `std::uint64_t` で、$0 \le n < 2^{64}$ を扱います。$0,1$ は `false` を返します。
- 時間計算量は $O(\log(n+1))$、空間計算量は $O(1)$ です。
- 乗算に `__uint128_t` を使います。
