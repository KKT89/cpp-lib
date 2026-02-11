---
tags:
  - tree
  - lca
---

# Lowest Common Ancestor

木上の LCA を `build: O(N)`, `query: O(1)` で処理する実装です。

## Interface

```cpp
LowestCommonAncestor lca(n);
lca.add_edge(u, v);
lca.build(root);
int a = lca.lca(u, v);
```

## Verify

- [Library Checker - LCA](../../verify/tree/lowest_common_ancestor.library_checker_lca.md)

## Code

```cpp
--8<-- "include/tree/lowest_common_ancestor.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/tree/lowest_common_ancestor.hpp"
```
