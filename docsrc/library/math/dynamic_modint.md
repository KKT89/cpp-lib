# modint (dynamic)

テンプレート引数 `id` ごとに法を持つ動的 modint です。複数の mod を同時に扱えます。`/` と `inv()` を使う場合は mod が素数で、`mod < 2^{63}` であることを仮定します。

## Interface

```cpp
using modint0 = dynamic_modint<0>;
using modint1 = dynamic_modint<1>;

modint0::set_mod(1000000007);     // 利用前に mod を設定 (64bit OK)
modint1::set_mod(998244353);      // id ごとに別の mod を設定できる

modint0 a = 42;                   // 値を構築
modint0 b = a / 5;                // O(log mod)
long long v = b.val();            // O(1)
modint0 c = modint0(2).pow(10);   // O(log n)
```

## Notes

- 利用前に `set_mod(m)` を呼ぶ必要があります。
- `/` と `inv()` を使う場合は mod が素数で、`mod < 2^{63}` であることを仮定します。
- 同じ `id` の `dynamic_modint` は同じ mod を共有します。
- 同時に複数の mod を保持しないなら、同じ `id` に対して `set_mod` を呼び直して使い回せます。
