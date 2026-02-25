# 連立一次方程式ソルバー

[Gauss-Jordan 法](gauss_jordan.md) を用いて連立一次方程式 $Ax = b$ を解くビルダー。
等式を `add` で追加し、`solve` で解を得る。

## Interface

```cpp
LinearSystem<T> sys(n);
sys.add(coeffs, rhs);                // 密形式: 係数ベクトル全体を渡す
sys.add({{idx, val}, ...}, rhs);     // 疎形式: 非ゼロ項のみ {変数インデックス, 係数} で渡す
optional<vector<T>> x = sys.solve(); // 一意解、解なし・不定は nullopt
```

| 操作 | 計算量 |
|------|--------|
| `add(...)` | $O(n)$ |
| `solve()` | $O(n^3)$ |

## Example

```cpp
LinearSystem<double> sys(3);  // x0, x1, x2 の 3 変数

sys.add({{1, 1.0}, {2, 1.0}}, 5.0);  // x1 + x2 = 5        (疎形式)
sys.add({1.0, 2.0, 1.0}, 8.0);        // x0 + 2*x1 + x2 = 8 (密形式)
sys.add({{0, 1.0}, {2, 1.0}}, 4.0);  // x0 + x2 = 4         (疎形式)

auto x = sys.solve();  // x = {1, 2, 3}
```

## Code

```cpp
--8<-- "include/math/linear_solve.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/linear_solve.hpp"
```
