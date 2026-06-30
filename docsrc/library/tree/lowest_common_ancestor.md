# Lowest Common Ancestor

木上の LCA と 2 頂点間の距離を `build: O(N)`, `query: O(1)` で求める実装です。

## Interface

```cpp
LowestCommonAncestor lca(n);   // n 頂点で初期化
lca.add_edge(u, v);            // 木の辺を追加
lca.build(root);               // 根 root で前処理
int p = lca.lca(u, v);         // LCA を取得
int d = lca.distance(u, v);    // u, v 間の距離（辺数）を取得
```
