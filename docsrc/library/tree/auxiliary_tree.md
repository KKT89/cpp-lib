---
tags:
  - tree
  - virtual_tree
---

# Auxiliary Tree (Virtual Tree)

与えられた頂点集合 `X` から補助木（Virtual Tree）を構築する実装です。

## Interface

```cpp
SchieberVishkinLCA lca(n);
// ... add_edge
lca.build(root);

AuxiliaryTree aux(lca, root);
int aux_root = aux.build(nodes);
// aux.g_aux: parent -> child, aux.nodes: aux木に含まれる頂点
```

## Code

```cpp
--8<-- "include/tree/auxiliary_tree.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/tree/auxiliary_tree.hpp"
```
