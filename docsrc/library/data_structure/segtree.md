# Segment Tree

モノイド $(S, \text{op}, e)$ 上の一点更新・区間クエリを処理するセグメント木。非再帰実装。

## Interface

```cpp
segtree<S, op, e> seg(n);          // 長さ n, 全要素 e() で初期化
segtree<S, op, e> seg(v);          // vector v で初期化
S  x = seg[i];                     // i 番目の要素を取得
seg.set(i, x);                     // i 番目の要素を x に更新
S  x = seg.query(l, r);            // [l, r) の op 集約値を取得
```

| 操作 | 計算量 |
|------|--------|
| `segtree(n)`, `segtree(v)` | $O(n)$ |
| `set(i, x)` | $O(\log n)$ |
| `query(l, r)` | $O(\log n)$ |
| `operator[](i)` | $O(1)$ |

## Code

```cpp
--8<-- "include/data_structure/segtree.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/data_structure/segtree.hpp"
```
