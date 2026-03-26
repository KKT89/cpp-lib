# 動的 modint

テンプレート引数 `id` を変えることで複数の mod を同時に扱える動的 modint です。mod は素数、mod < $2^{63}$ の制約があります。`+`, `-`, `*`, `/`, `pow`, `inv` をサポートしています。

## Interface

```cpp
using modint0 = dynamic_modint<0>;
using modint1 = dynamic_modint<1>;

modint0::set_mod(1000000007);        // mod を設定 (64bit OK)
modint1::set_mod(998244353);

modint0 a = 42;
long long v = a.val();               // 生の値を取得
```

| 操作 | 計算量 |
|------|--------|
| `set_mod(m)` | $O(1)$ |
| `+`, `-`, `*` | $O(1)$ |
| `/`, `inv()` | $O(\log \mathrm{mod})$ |
| `pow(n)` | $O(\log n)$ |

## Tips

ループ内で毎回異なる mod を使いたいが同時に複数 mod を保持する必要がない場合、同じ id で `set_mod` を呼び直せばよい。

```cpp
using modint = dynamic_modint<0>;
for (int i = 0; i < 5; ++i) {
    modint::set_mod(p);   // 毎回 mod を上書き
    // modint を使って計算 ...
}
```

テンプレート引数はコンパイル時定数なので `dynamic_modint<i>` のようにループ変数を渡すことはできない。
複数 mod を同時に使う必要がある場合は `dynamic_modint<0>`, `dynamic_modint<1>`, ... と id を分ける。

## Code

```cpp
--8<-- "include/math/dynamic_modint.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/dynamic_modint.hpp"
```
