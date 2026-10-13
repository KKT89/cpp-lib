# Segment Tree

モノイド $(S, \text{op}, e)$ 上の一点更新・区間クエリを非再帰で処理するセグメント木です。

## Interface

```cpp
SegmentTree<S, op, e> seg(n);   // 長さ n, 全要素 e() で初期化
SegmentTree<S, op, e> seg(v);   // vector v で初期化
S x = seg.query(l, r);          // [l, r) の op 集約値を取得, O(log n)
S x = seg[i];                   // i 番目の要素を取得, O(1)
seg.set(i, x);                  // i 番目の要素を x に更新, O(log n)
int r = seg.max_right(l, f);    // f(query(l, r)) を満たす最大 r, O(log n)
int l = seg.min_left(r, f);     // f(query(l, r)) を満たす最小 l, O(log n)
```

## Template

```cpp
#include "segtree/segtree.hpp"

S op(S a, S b) {

}

S e() {

}

using Seg = SegmentTree<S, op, e>;
```

## Notes

- 探索の判定 `f` は `f(e()) == true` を満たし、区間を伸ばすと `true` から `false` にだけ変化する必要があります。
