# 二項係数

mod 素数での二項係数を計算します。階乗テーブルは範囲外アクセス時に自動拡張されます。

## Interface

```cpp
using modint = static_modint<998244353>;
Combination<modint, 1 << 20> comb;  // [0, 2^20] を前計算

modint a = comb.comb(10, 3);             // C(10, 3) (n < mod 前提)
modint b = comb.comb(1 << 21, 5);        // 範囲外 → 自動拡張
modint c = comb.big_comb(1e18, 5);       // n が modint のとき (r が小さい場合)
modint d = comb.lucas(1e15, 3);            // n >= mod でも OK (Lucas の定理)
```

| 操作 | 計算量 |
|------|--------|
| `Combination()` | $O(N + \log \mathrm{mod})$ |
| `extend(n)` | 拡張分に対して $O(\Delta + \log \mathrm{mod})$ |
| `comb(n, r)` | 償却 $O(1)$（拡張時を除く） |
| `big_comb(n, r)` | $O(r)$ |
| `lucas(n, r)` | $O(\mathrm{mod} + \log_{\mathrm{mod}} n)$ |

## Notes

- `comb(n, r)` は `n < mod` が前提です。`n >= mod` のときは `0` を返します。
- `lucas(n, r)` は `n >= mod` でも正しく計算します。mod は `T::get_mod()` から取得します。内部で `comb` を呼ぶため、初回呼び出し時に `mod - 1` まで自動拡張されます。
- `comb(n, r)` は `r < 0` または `n < r` のとき `0` を返します。
- `big_comb(n, r)` は `n` が大きく `r < mod` の場合に使います。`n` は modint 型で渡します。`r >= mod` のときは `0` を返します。
- `extend(n)` は現在のテーブルサイズ以下の `n` では何もしません。

## Code

```cpp
--8<-- "include/math/combination.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/combination.hpp"
```
