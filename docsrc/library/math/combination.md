# 二項係数

`mod` が素数のときの二項係数を計算します。階乗テーブルは必要に応じて自動拡張します。

## Interface

```cpp
using modint = static_modint<998244353>;
Combination<modint, 1 << 20> comb;                            // [0, 2^20] を前計算

modint a = comb.comb(10, 3);                                  // C(10, 3), 償却 O(1) (n < mod 前提)
modint b = comb.comb(1 << 21, 5);                             // 範囲外なら自動拡張
modint c = comb.big_comb(modint(1000000000000000000LL), 5);   // n が大きく r が小さい場合, O(r)
modint d = comb.lucas(1000000000000000LL, 3);                 // n >= mod でも OK
```

## Notes

- `mod` が素数であることを仮定します。
- `comb(n, r)` は `n < mod` が前提で、`r < 0`, `n < r`, `n >= mod` のとき `0` を返します。
- `big_comb(n, r)` は `r < mod` を想定し、`r >= mod` のとき `0` を返します。
- `lucas(n, r)` は初回呼び出し時に `mod - 1` まで自動拡張します。
