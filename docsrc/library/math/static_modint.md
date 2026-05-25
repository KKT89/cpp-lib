# modint (static)

コンパイル時定数の mod を持つ modint です。

## Interface

```cpp
constexpr int MOD = 998244353;
using modint = static_modint<MOD>;

modint a = 42;
modint b = a / 5;               // O(log mod)
int v = b.val();                // O(1)
modint c = modint(2).pow(10);   // O(log n)
```

## Notes

- `1 <= mod` を想定します。
- `/` と `inv()` を使う場合は mod が素数であることを仮定します。
