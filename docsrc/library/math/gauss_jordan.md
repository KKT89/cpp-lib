# Gauss-Jordan 法

ガウス・ジョルダン法 (掃き出し法) により行列を簡約行階段形に変換し、rank を返す。
浮動小数点型では部分ピボット選択による数値安定化、有理数型・剰余体型など厳密な型では `eps=0` の完全一致比較で動作する。

連立方程式を解きたい場合は [LinearSystem](linear_solve.md) を使用する。

## Interface

```cpp
int rank = gauss_jordan(A);        // 拡大係数行列 [A|b] として処理 (augmented=true)
int rank = gauss_jordan(A, false); // 係数行列として処理 (rank 計算・逆行列など)
```

| 操作 | 計算量 |
|------|--------|
| `gauss_jordan(A)` | $O(n^2 m)$ |

($n$: 行数, $m$: 列数)

## Code

```cpp
--8<-- "include/math/gauss_jordan.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/gauss_jordan.hpp"
```
