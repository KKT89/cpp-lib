# Range Tree

候補点を事前登録し、可換モノイド上の一点更新と二次元矩形積を処理します。

## Interface

```cpp
RangeTree<S, op, e, T> tree;
tree.add_point(x, y);                   // 更新候補点 (x, y) を登録
tree.build();                           // 登録した候補点から構築, O(N log N)
tree.add(x, y, value);                  // (x, y) の値を op(現在値, value) に更新, O(log^2 N)
tree.set(x, y, value);                  // (x, y) の値を value に更新, O(log^2 N)
S value = tree.get(x, y);               // (x, y) の値を取得, O(log N)
S result = tree.prod(xl, xr, yl, yr);   // [xl, xr) x [yl, yr) の積を取得, O(log^2 N)
```

## Notes

- `op` は可換である必要があります。
- `add_point` をすべて呼んだ後に `build` を一度だけ呼びます。
- `add`、`set`、`get` には、`add_point` で登録した点を指定します。
- 各点の初期値は `e()` です。
