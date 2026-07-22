# Dual Segment Tree

モノイド作用で区間作用・1点取得を処理する双対セグメント木です。

## Interface

```cpp
DualSegmentTree<S, e, F, mapping, composition, id> seg(n);      // 長さ n, 全要素 e() で初期化
DualSegmentTree<S, e, F, mapping, composition, id> seg(n, x);   // 長さ n, 全要素 x で初期化
DualSegmentTree<S, e, F, mapping, composition, id> seg(v);      // vector v で初期化
seg.apply(l, r, f);                                             // [l, r) に作用 f を適用, O(log n)
seg.set(i, x);                                                  // i 番目の値を x に更新, O(log n)
S x = seg.get(i);                                               // i 番目の値を取得, O(log n)
S x = seg[i];                                                   // i 番目の値を取得, O(log n)
```

## Notes

- `S` は値の型、`F` は作用の型です。
- `mapping(f, x)` は値 `x` に作用 `f` を適用した結果を返します。
- `composition(f, g)` は `g` の後に `f` を適用する合成を返します。つまり `mapping(composition(f, g), x) == mapping(f, mapping(g, x))` を満たす必要があります。
- `id()` は作用の単位元を返します。
