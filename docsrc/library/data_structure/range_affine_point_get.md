---
parent: data_structure/dual_segtree.hpp
---

# Range Affine Point Get

[`dual_segtree`](dual_segtree.md) を使って、区間アフィン変換・1点取得を処理します。

## Interface

```cpp
range_affine_point_get<T> seg(n);      // 長さ n, 全要素 T() で初期化
range_affine_point_get<T> seg(n, x);   // 長さ n, 全要素 x で初期化
range_affine_point_get<T> seg(v);      // vector v で初期化
seg.apply(l, r, a, b);                 // [l, r) の各 x を a * x + b に更新, O(log n)
seg.set(i, x);                         // i 番目の値を x に更新, O(log n)
T x = seg.get(i);                      // i 番目の値を取得, O(log n)
T x = seg[i];                          // i 番目の値を取得, O(log n)
```