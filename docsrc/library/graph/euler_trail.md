# 無向オイラー路

無向グラフのオイラー路を 1 つ求めます。多重辺・自己ループに対応しています。

## Interface

```cpp
UndirectedEulerTrail et(n);       // n 頂点で初期化
int id = et.add_edge(u, v);       // 無向辺を追加し、辺 id を返す
bool ok = et.build();             // 始点を自動で選ぶ, O(V + E)
bool ok = et.build(s);            // 始点 s を指定する, O(V + E)

const auto &vs = et.vertices();   // オイラー路の頂点列, 長さ E + 1
const auto &es = et.edge_ids();   // 通った辺 id の列, 長さ E
```

`build` は、オイラー路が存在しない場合や、指定した始点から全ての辺を通れない場合に `false` を返します。
