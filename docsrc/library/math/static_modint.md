# 静的 modint

コンパイル時定数の mod を持つ modint です。`+`, `-`, `*`, `/`, `pow`, `inv` をサポートしています。`/` と `inv` はフェルマーの小定理を使うため、mod が素数であることを仮定します。制約は ACL と同様に `1 <= mod` です。

## Interface

```cpp
constexpr int MOD = 998244353;
using modint = static_modint<MOD>;

modint a = 42;
modint b = a / 5;
int v = b.val();
modint c = modint(2).pow(10);
```

| 操作 | 計算量 |
|------|--------|
| `+`, `-`, `*`, `/` | $O(1)$ |
| `pow(n)` | $O(\log n)$ |
| `inv()` | $O(\log \mathrm{mod})$ |

## Notes

- `int64_t` から構築できます。
- `pow(n)` は `n >= 0` を想定しています。
- ACL と同様にテンプレート引数 `mod` は正の `int` を想定しています。

## Code

```cpp
--8<-- "include/math/static_modint.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/static_modint.hpp"
```
