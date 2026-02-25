# Auxiliary Tree (Virtual Tree)

与えられた頂点集合 `X` から補助木（Virtual Tree）を構築する実装です。

## Interface

```cpp
LowestCommonAncestor lca(n);
// ... add_edge
lca.build(root);

AuxiliaryTree aux(lca);
int aux_root = aux.build(nodes);
// aux.g_aux: parent -> child
// aux.nodes: aux 木に含まれる頂点（preorder 順）
```

| 操作 | 計算量 |
|------|--------|
| `AuxiliaryTree(lca)` | $O(n)$ |
| `build(X)` | $O(k \log k)$ |

($k = |X|$、LCA クエリは $O(1)$ を仮定)

## Code

```cpp
--8<-- "include/tree/auxiliary_tree.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/tree/auxiliary_tree.hpp"
```
