# Bellman Ford (負閉路検出)

単一始点（または複数始点）の最短路を求め、負閉路の影響を受ける頂点を検出する実装です。

## Interface

```cpp
BellmanFord<int> bf(n);
bf.add_edge(from, to, cost);
bf.build(s);                                // 単一始点
bf.build(sources.begin(), sources.end());   // 複数始点

bool ok    = bf.valid(v);
bool reach = bf.reachable(v);
bool neg   = bf.on_negative_cycle(v);
int  d     = bf.distance(v);
```

| 操作 | 計算量 |
|------|--------|
| `BellmanFord(n)` | $O(n)$ |
| `add_edge(from, to, cost)` | $O(1)$ |
| `build(s)` | $O(VE)$ |
| `valid(v)`, `distance(v)` 等 | $O(1)$ |

## Reference

- [ABC137-E:Coins Respawn ~負閉路検出について~ - 思考の墓場](https://sigma1113.hatenablog.com/entry/2019/08/12/130042)

## Code

```cpp
--8<-- "include/graph/bellman_ford.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/graph/bellman_ford.hpp"
```
