# modint (static)

コンパイル時定数の mod を持つ modint です。ACL と同様に `1 <= mod` を想定し、`/` と `inv()` では mod が素数であることを仮定します。

## Interface

```cpp
constexpr int MOD = 998244353;
using modint = static_modint<MOD>;

modint a = 42;
modint b = a / 5;               // O(log mod)
int v = b.val();                // O(1)
modint c = modint(2).pow(10);   // O(log n)
```

`get_mod()`, `val()`, `+`, `-`, `*` は $O(1)$ です。

## Notes

- ACL と同様に `1 <= mod` を想定します。
- `/` と `inv()` を使う場合は mod が素数であることを仮定します。
- `pow(n)` は `n >= 0` を想定します。
