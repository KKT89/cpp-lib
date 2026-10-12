---
parent: segtree/lazy_segtree.hpp
---

# Range Add Range Sum

[`LazySegmentTree`](lazy_segtree.md) を使って、区間加算・区間和取得を処理します。区間長を内部で管理し、値型 `T` だけで操作します。

## Interface

```cpp
RangeAddRangeSum<T> seg(n);      // 数値型 T の n 要素を 0 で初期化
RangeAddRangeSum<T> seg(n, x);   // 長さ n, 全要素 x で初期化
RangeAddRangeSum<T> seg(v);      // vector v で初期化
seg.add(l, r, x);                // [l, r) に x を加算, O(log n)
seg.set(i, x);                   // i 番目の値を x に更新, O(log n)
T x = seg.query(l, r);           // [l, r) の和を取得, O(log n)
T x = seg.all_query();           // 全体の和を取得, O(1)
T x = seg.get(i);                // i 番目の値を取得, O(log n)
T x = seg[i];                    // i 番目の値を取得, O(log n)
```

## Example

```cpp
RangeAddRangeSum<long long> seg(std::vector<long long>{1, 2, 3});
seg.add(0, 2, 4);                                                   // 値は {5, 6, 3}
long long sum = seg.query(0, 3);                                    // 14
```
