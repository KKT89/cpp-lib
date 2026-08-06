# Line2D

2 次元の線分・直線と、交差判定・射影・距離を扱います。

## Interface

```cpp
geometry::Segment<geometry::Real> s(a, b);   // double 座標の線分を作成
geometry::Segment<geometry::Real> t(c, d);   // double 座標の線分を作成
geometry::Line<geometry::Real> l(a, b);      // double 座標の直線を作成
geometry::Segment<long long> si(e, f);       // 整数座標の線分を作成
bool ok = geometry::intersects(s, t);        // 2 線分が交差するか判定
bool para = geometry::is_parallel(l, m);     // 2 直線が平行か判定
auto p = geometry::projection(l, q);         // q を直線 l へ射影
double d = geometry::distance(s, q);         // 線分 s と点 q の距離を取得
```

## Notes

- `geometry::Segment<T>` / `geometry::Line<T>` は座標型 `T` のテンプレートで、`double` 座標は `geometry::Segment<geometry::Real>` のように使います。
- `intersects` / `is_parallel` / `is_orthogonal` は整数座標でも使えます。
- `projection` / `reflection` / `crosspoint` は割り算が必要なため、`geometry::Field`（整数型を除いた割り算可能な型。浮動小数点や有理数）で使えます。整数型は切り捨て除算で誤るため弾きます。
- `distance` は平方根が必要なため浮動小数点座標で使います。
- `geometry::S` / `geometry::L` は `double` 座標、`geometry::Si` / `geometry::Li` は `long long` 座標のエイリアスです。コンストラクタは CTAD に対応し、`Segment s(a, b);` のように座標型を推論します。
