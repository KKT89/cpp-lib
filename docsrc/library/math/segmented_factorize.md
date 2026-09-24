# 区間素因数分解

区間篩により、閉区間 $[L, R]$ の各整数をまとめて素因数分解します。
内部で [線形篩](linear_sieve.md) を使って $\lfloor\sqrt{R}\rfloor$ 以下の素数を求め、区間内の倍数から素因数を取り除きます。

## Interface

```cpp
auto factors = segmented_factorize(L, R);   // [L, R] をまとめて分解
auto ps = factors[x - L];                   // x の (素因数, 指数) を昇順で列挙
```

## Notes

- `L`, `R` は `long long` で、$1 \le L \le R$ を仮定します。
- 返り値は `vector<vector<pair<long long, int>>>` で、$1$ の分解結果は空です。
- $W = R-L+1$ として、時間計算量は $O(\sqrt{R} + W\log(R+1))$、結果を除く空間計算量は $O(\sqrt{R}+W)$ です。
- 篩は呼び出しごとに構築します。
