# Bellman Ford (負閉路検出)

## Reference

- [ABC137-E:Coins Respawn ~負閉路検出について~ - 思考の墓場](https://sigma1113.hatenablog.com/entry/2019/08/12/130042)

## Code

```cpp
#pragma once

template <typename T> struct BellmanFord {
  private:
    static constexpr T INF = numeric_limits<T>::max() / 2 - 1;

    struct Edge {
        int to;
        T cost;
    };

    int n;
    vector<vector<Edge>> G;
    vector<T> dist;

  public:
    explicit BellmanFord(int n) : n(n), G(n), dist(n, INF) {}

    void add_edge(int from, int to, T cost) { G[from].emplace_back(to, cost); }
    template <class Iter> void build(Iter first, Iter last) {
        dist.assign(n, INF);
        for (auto it = first; it != last; ++it) {
            dist[*it] = 0;
        }
        relax_edges();
        spread_neg_cycles();
    }
    void build(int s) { build(&s, &s + 1); }

    [[nodiscard]] bool reachable(int v) const { return dist[v] != INF; }
    [[nodiscard]] bool on_negative_cycle(int v) const { return dist[v] == -INF; }
    [[nodiscard]] bool valid(int v) const { return reachable(v) and !on_negative_cycle(v); }
    [[nodiscard]] T distance(int v) const { return dist[v]; }

  private:
    // ベルマンフォード
    void relax_edges() {
        for (int i = 0; i < n; ++i) {
            bool updated = false;
            for (int u = 0; u < n; ++u) {
                if (dist[u] == INF) continue;
                for (auto [v, w] : G[u]) {
                    if (dist[v] > dist[u] + w) {
                        dist[v] = dist[u] + w;
                        if (i == n - 1 || dist[v] < -INF) dist[v] = -INF;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }
    }
    // 負閉路をBFSで伝播させる
    void spread_neg_cycles() {
        queue<int> q;
        vector<bool> used(n, false);
        for (int i = 0; i < n; ++i) {
            if (dist[i] == -INF) {
                used[i] = true;
                q.push(i);
            }
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto [v, w] : G[u]) {
                if (!used[v]) {
                    used[v] = true;
                    dist[v] = -INF;
                    q.push(v);
                }
            }
        }
    }
};
```