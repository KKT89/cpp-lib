# Point2D

2 次元の点・ベクトルと、内積・外積・位置関係判定を扱います。

## Interface

```cpp
geometry::Point<geometry::Real> p(x, y);   // double 座標の点を作成
geometry::Point<long long> q(a, b);        // 整数座標の点を作成
auto inner = geometry::dot(p, p);          // 内積を取得
auto outer = geometry::cross(p, p);        // 外積を取得
auto sq = geometry::norm(p);               // 長さの 2 乗を取得
double len = geometry::length(p);          // 長さを取得
int pos = geometry::ccw(a, b, c);          // 3 点の位置関係を取得
```

## Notes

- `geometry::Point<T>` は座標型 `T` のテンプレートで、`double` 座標は `geometry::Point<geometry::Real>`、整数座標は `geometry::Point<long long>` を使います。
- `norm` は長さの 2 乗を返し、`length` は平方根を取った長さを返します。
- 整数座標の `dot` / `cross` / `norm` は内部で `__int128_t` に広げます。
- `geometry::P` は `Point<geometry::Real>`、`geometry::Pi` は `Point<long long>` のエイリアスです。
- `ccw(a, b, c)` は AOJ CGL の慣例に合わせて、反時計回り `1`、時計回り `-1`、`c-a-b` の順で一直線上 `2`、`a-b-c` の順で一直線上 `-2`、線分 `ab` 上 `0` を返します。
