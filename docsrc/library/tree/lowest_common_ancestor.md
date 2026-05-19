# Lowest Common Ancestor

木上の LCA を `build: O(N)`, `query: O(1)` で処理する実装です。

## Interface

```cpp
LowestCommonAncestor lca(n);

// 木の辺を追加
lca.add_edge(u, v);

// 根 root で前処理
lca.build(root);

// LCA を取得
int p = lca.lca(u, v);
```

| 操作 | 計算量 |
|------|--------|
| `LowestCommonAncestor(n)` | $O(n)$ |
| `add_edge(u, v)` | $O(1)$ |
| `build(root)` | $O(n)$ |
| `lca(u, v)` | $O(1)$ |

