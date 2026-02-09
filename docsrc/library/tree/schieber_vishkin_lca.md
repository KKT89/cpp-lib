---
tags:
  - tree
  - lca
---

# Schieber-Vishkin LCA

木上の LCA を `build: O(N)`, `query: O(1)` で処理する実装です。

## Interface

```cpp
SchieberVishkinLCA lca(n);
lca.add_edge(u, v);
lca.build(root);
int a = lca.lca(u, v);
```

## Verify

- [Library Checker - Lowest Common Ancestor](https://judge.yosupo.jp/problem/lca)
- `verify/tree/schieber_vishkin_lca/library_checker_lca.test.cpp`

## Code

```cpp
--8<-- "include/tree/schieber_vishkin_lca.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/tree/schieber_vishkin_lca.hpp"
```
