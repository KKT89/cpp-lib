# Segment Tree

モノイド $(S, \text{op}, e)$ 上の一点更新・区間クエリを非再帰で処理するセグメント木です。

## Interface

```cpp
SegmentTree<S, op, e> seg(n);   // 長さ n, 全要素 e() で初期化
SegmentTree<S, op, e> seg(v);   // vector v で初期化
S x = seg.query(l, r);          // [l, r) の op 集約値を取得, O(log n)
S x = seg[i];                   // i 番目の要素を取得, O(1)
seg.set(i, x);                  // i 番目の要素を x に更新, O(log n)
```
