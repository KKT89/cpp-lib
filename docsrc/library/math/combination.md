# 二項係数

`mod` が素数のときの二項係数を計算します。階乗テーブルは必要に応じて自動拡張します。

## Interface

```cpp
using modint = static_modint<998244353>;
Combination<modint, 1 << 20> comb;              // [0, 2^20] を前計算

modint a = comb.comb(10, 3);                    // C(10, 3), 償却 O(1)
modint b = comb.comb(1 << 21, 5);               // 範囲外なら自動拡張
modint c = comb.big_comb(modint(1 << 51), 5);   // n が大きく r が小さい場合, O(r)
```

## Notes

- `mod` が素数であることを仮定します。
