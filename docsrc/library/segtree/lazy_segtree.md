# Lazy Segment Tree

モノイド $(S, \text{op}, e)$ とモノイド作用で、区間作用・区間クエリを非再帰で処理する遅延セグメント木です。

## Interface

```cpp
using LazySeg = LazySegmentTree<S, op, e, F, mapping, composition, id>;
LazySeg seg(n);                                                           // 長さ n, 全要素 e() で初期化
LazySeg seg(n, x);                                                        // 長さ n, 全要素 x で初期化
LazySeg seg(v);                                                           // vector v で初期化
seg.apply(l, r, f);                                                       // [l, r) に作用 f を適用, O(log n)
seg.apply(i, f);                                                          // i 番目に作用 f を適用, O(log n)
seg.set(i, x);                                                            // i 番目の値を x に更新, O(log n)
S x = seg.query(l, r);                                                    // [l, r) の op 集約値を取得, O(log n)
S x = seg.all_query();                                                    // 全体の op 集約値を取得, O(1)
S x = seg.get(i);                                                         // i 番目の値を取得, O(log n)
S x = seg[i];                                                             // i 番目の値を取得, O(log n)
```

## Template

```cpp
#include "segtree/lazy_segtree.hpp"

S op(S a, S b) {

}

S e() {

}

S mapping(F f, S x) {

}

F composition(F f, F g) {

}

F id() {

}

using LazySeg = LazySegmentTree<S, op, e, F, mapping, composition, id>;
```

## Notes

- `S` は集約値の型、`F` は作用の型です。`op` と `e()` はモノイドを定義します。
- `mapping(f, x)` は集約値 `x` に作用 `f` を適用した結果を返します。`op` との整合性 `mapping(f, op(x, y)) == op(mapping(f, x), mapping(f, y))` を満たす必要があります。
- `composition(f, g)` は `g` の後に `f` を適用する合成を返します。つまり `mapping(composition(f, g), x) == mapping(f, mapping(g, x))` を満たす必要があります。`id()` は作用の単位元を返します。
- 区間は `0 <= l <= r <= n`、位置は `0 <= i < n` を指定します。構築時間・使用領域は $O(n)$ です。
