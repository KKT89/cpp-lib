# 重み付き Union-Find

各要素に重みを持たせた Union-Find。`unite(x, y, w)` で $\text{weight}(y) - \text{weight}(x) = w$ という差分制約を課し、矛盾検出を行う。

## Interface

```cpp
WeightedUnionFind<T> uf(n);
bool ok  = uf.unite(x, y, w);   // weight(y) - weight(x) = w を課す (矛盾時 false)
bool con = uf.same(x, y);       // 同じ連結成分か
T    d   = uf.diff(x, y);       // weight(y) - weight(x)
T    w   = uf.weight(x);        // x の重み
int  s   = uf.size(x);          // x が属する連結成分のサイズ
int  r   = uf.find(x);          // x の根
```

| 操作 | 計算量 |
|------|--------|
| `WeightedUnionFind(n)` | $O(n)$ |
| `unite(x, y, w)` | $O(\alpha(n))$ |
| `same`, `diff`, `weight`, `size`, `find` | $O(\alpha(n))$ |

## Verify

- [AOJ 3327 - Beam Beam Beam](../../verify/aizu/3327.md)

## Code

```cpp
--8<-- "include/graph/weighted_union_find.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/graph/weighted_union_find.hpp"
```
