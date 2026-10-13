---
parent: segtree/lazy_segtree.hpp
---

# Range Add Range Min

[`LazySegmentTree`](lazy_segtree.md) を使って、区間加算・区間最小値取得を処理します。

## Interface

```cpp
RangeAddRangeMin<T> seg;         // 空の木を構築
RangeAddRangeMin<T> seg(n);      // 長さ n, 全要素 T() で初期化
RangeAddRangeMin<T> seg(n, x);   // 長さ n, 全要素 x で初期化
RangeAddRangeMin<T> seg(v);      // vector v で初期化
seg.add(l, r, x);                // [l, r) に x を加算, O(log n)
seg.set(i, x);                   // i 番目の値を x に更新, O(log n)
T x = seg.query(l, r);           // [l, r) の最小値を取得, O(log n)
T x = seg.all_query();           // 全体の最小値を取得, O(1)
T x = seg.get(i);                // i 番目の値を取得, O(log n)
T x = seg[i];                    // i 番目の値を取得, O(log n)
```

## Notes

- 空区間の `query(l, l)` と空の木の `all_query()` は `std::numeric_limits<T>::max()` を返します。この値を空区間用に予約し、実値・加算後の実値には使いません。
- 値と遅延加算の合成結果は `T` の範囲に収めます。
