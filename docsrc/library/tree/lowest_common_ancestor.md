# Lowest Common Ancestor

木上の LCA を `build: O(N)`, `query: O(1)` で求める実装です。

## Interface

```cpp
LowestCommonAncestor lca(n);   // n 頂点で初期化
lca.add_edge(u, v);            // 木の辺を追加
lca.build(root);               // 根 root で前処理
int p = lca.lca(u, v);         // LCA を取得
```
