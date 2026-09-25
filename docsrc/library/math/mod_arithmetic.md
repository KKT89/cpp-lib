# 剰余演算

64bit 非負整数の剰余乗算・累乗を計算します。

## Interface

```cpp
auto x = mod_mul(a, b, mod);   // a * b mod mod, O(1)
auto y = mod_pow(a, n, mod);   // a^n mod mod, O(log(n + 1))
```

## Notes

- 引数・返り値は `std::uint64_t` です。$a,b,n$ は非負とし、$1 \le \mathrm{mod} < 2^{64}$ を仮定します。
- 乗算の中間値に `__uint128_t` を使い、返り値を $[0,\mathrm{mod})$ に収めます。
- `mod_pow(a, 0, mod)` は $1 \bmod \mathrm{mod}$ を返します。法が $1$ なら常に $0$ です。
- 空間計算量は $O(1)$ です。
