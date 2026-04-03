# Union Find

素集合データ構造です。経路圧縮とサイズによるマージを行います。

## Interface

```cpp
UnionFind uf(n);           // n 頂点で初期化
uf.unite(u, v);            // u と v を併合
bool b = uf.same(u, v);   // u と v が同じ連結成分か
int s = uf.size(v);        // v の属する連結成分のサイズ
int r = uf.find(v);        // v の根を取得
```

| 操作 | 計算量 |
|------|--------|
| `UnionFind(n)` | $O(n)$ |
| `find(v)` | $O(\alpha(n))$ |
| `unite(u, v)` | $O(\alpha(n))$ |
| `same(u, v)` | $O(\alpha(n))$ |
| `size(v)` | $O(\alpha(n))$ |

## Code

```cpp
--8<-- "include/data_structure/union_find.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/data_structure/union_find.hpp"
```
