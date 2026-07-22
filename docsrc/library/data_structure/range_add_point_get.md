---
parent: data_structure/dual_segtree.hpp
---

# Range Add Point Get

[`DualSegmentTree`](dual_segtree.md) を使って、区間加算・1点取得を処理します。

## Interface

```cpp
RangeAddPointGet<T> seg(n);      // 長さ n, 全要素 T() で初期化
RangeAddPointGet<T> seg(n, x);   // 長さ n, 全要素 x で初期化
RangeAddPointGet<T> seg(v);      // vector v で初期化
seg.add(l, r, x);                // [l, r) に x を加算, O(log n)
T x = seg.get(i);                // i 番目の値を取得, O(log n)
T x = seg[i];                    // i 番目の値を取得, O(log n)
```
