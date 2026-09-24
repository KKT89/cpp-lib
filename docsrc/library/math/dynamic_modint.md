# modint (dynamic)

テンプレート引数 `id` ごとに法を持つ動的 modint です。複数の mod を同時に扱えます。

## Interface

```cpp
using modint0 = dynamic_modint<0>;
using modint1 = dynamic_modint<1>;

modint0::set_mod(1000000007);        // 利用前に mod を設定
modint1::set_mod(998244353);         // id ごとに別の mod を設定できる

modint0 a = 42;
modint0 b = a / 5;                   // O(log mod)
unsigned long long v = b.val();      // O(1)
modint0 c = modint0(2).pow(10);      // O(log n)
```

## Notes

- 法は $1 \le m < 2^{63}$ とします。
- `/` と `inv()` は法が素数で、除数・逆元を求める値が非零であることを仮定します。`pow(n)` は $n \ge 0$ 用です。
- `set_mod` で法を変えた後は、同じ `id` の既存の値を作り直してください。
