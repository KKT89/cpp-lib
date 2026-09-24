# 二項係数

階乗・逆階乗テーブルを使って二項係数を計算します。テーブルは必要に応じて拡張します。

## Interface

```cpp
using modint = static_modint<998244353>;
Combination<modint, 1 << 20> comb;                // [0, 2^20] を前計算

modint a = comb.comb(10, 3);                      // C(10, 3), 前計算済みかつ n < mod なら O(1)
modint b = comb.comb(1 << 21, 5);                 // 範囲外なら自動拡張
modint c = comb.big_comb(modint(1LL << 51), 5);   // n が大きく r が小さい場合, 前計算後 O(r)
```

## Notes

- `mod` が素数であることを仮定します。
- `comb(n, r)` は $n \ge \mathrm{mod}$ で Lucas の定理を使います。各桁の計算で、最大 $\mathrm{mod}-1$ までテーブルを拡張します。
- `big_comb(n, r)` は $0 \le r < \mathrm{mod}$ 用です。範囲外では $0$ を返します。
- テーブルを $k$ 要素拡張する時間は $O(k+\log\mathrm{mod})$ です。
