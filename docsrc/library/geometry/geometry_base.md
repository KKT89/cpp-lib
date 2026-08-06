# Geometry Base

幾何ライブラリで共通して使う符号判定、平方根、拡張整数型を提供します。

## Interface

```cpp
int s = geometry::sign(x);           // x の符号を取得
int t = geometry::sign(x, y);        // x - y の符号を取得
double r = geometry::safe_sqrt(x);   // 負の微小誤差を 0 に丸めて平方根を取得
geometry::EPS = 1e-9;                // 許容誤差を変更（既定 1e-8）
```

## Notes

- `geometry::Real` は `double` です。`geometry::EPS` は既定 `1e-8` で、`geometry::EPS = 1e-9;` のように利用側から変更できます。
- 浮動小数点型の `sign` は `EPS` を使い、それ以外の型では厳密に比較します。
- `geometry::calc_t<T>` は内部計算用の型で、整数型 `T` を `__int128_t` に広げ、それ以外の型はそのまま扱います。
- `geometry::Field` は整数型を除いた割り算可能な型（浮動小数点や有理数）を表す concept です。切り捨て除算で誤る整数型を弾き、`projection` などの割り算を含む幾何演算で使います。
