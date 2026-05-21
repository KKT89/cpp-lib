# Bellman Ford (負閉路検出)

単一始点（または複数始点）の最短路を求めます。負閉路の影響を受ける頂点の検出も可能です。

## Interface

```cpp
BellmanFord<int> bf(n);                     // 頂点数 n で初期化
bf.add_edge(from, to, cost);                // 有向辺を追加
bf.build(s);                                // 単一始点, O(VE)
bf.build(sources.begin(), sources.end());   // 複数始点, O(VE)

bool ok = bf.valid(v);                      // v の距離が定まるか
bool reach = bf.reachable(v);               // v が到達可能か
bool neg = bf.on_negative_cycle(v);         // v が負閉路の影響を受けるか
int d = bf.distance(v);                     // v までの最短距離
```
