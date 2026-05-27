#pragma once

#include <algorithm>
#include <vector>

struct UndirectedEulerTrail {
  private:
    struct Edge {
        int from, to;
        bool used;
    };

    int n;
    std::vector<Edge> edges;
    std::vector<std::vector<int>> g;
    std::vector<int> deg;
    std::vector<int> trail_vertices;
    std::vector<int> trail_edges;

  public:
    explicit UndirectedEulerTrail(int n = 0) : n(n), g(n), deg(n, 0) {}

    int add_edge(int u, int v) {
        int id = (int)edges.size();
        edges.push_back({u, v, false});
        g[u].push_back(id);
        g[v].push_back(id);
        ++deg[u];
        ++deg[v];
        return id;
    }

    // s == -1 のとき、存在すれば適当な始点を選ぶ
    bool build(int s = -1) {
        trail_vertices.clear();
        trail_edges.clear();
        for (auto &e : edges) e.used = false;

        if (n == 0) return edges.empty();

        std::vector<int> odd;
        for (int v = 0; v < n; ++v) {
            if (deg[v] % 2 == 1) odd.push_back(v);
        }
        if ((int)odd.size() != 0 && (int)odd.size() != 2) return false;

        if (s == -1) {
            if ((int)odd.size() == 2) {
                s = odd[0];
            } else {
                s = 0;
                for (int v = 0; v < n; ++v) {
                    if (deg[v] > 0) {
                        s = v;
                        break;
                    }
                }
            }
        }

        if (s < 0 || s >= n) return false;
        if (!edges.empty()) {
            if (deg[s] == 0) return false;
            if ((int)odd.size() == 2 && s != odd[0] && s != odd[1]) return false;
        }

        std::vector<int> iter(n, 0), st_vertices, st_edges;
        st_vertices.reserve(edges.size() + 1);
        st_edges.reserve(edges.size() + 1);
        trail_vertices.reserve(edges.size() + 1);
        trail_edges.reserve(edges.size() + 1);

        st_vertices.push_back(s);
        st_edges.push_back(-1);

        while (!st_vertices.empty()) {
            int v = st_vertices.back();
            while (iter[v] < (int)g[v].size() && edges[g[v][iter[v]]].used) {
                ++iter[v];
            }

            if (iter[v] == (int)g[v].size()) {
                trail_vertices.push_back(v);
                trail_edges.push_back(st_edges.back());
                st_vertices.pop_back();
                st_edges.pop_back();
                continue;
            }

            int id = g[v][iter[v]++];
            Edge &e = edges[id];
            e.used = true;
            int to = (e.from == v ? e.to : e.from);
            st_vertices.push_back(to);
            st_edges.push_back(id);
        }

        std::reverse(trail_vertices.begin(), trail_vertices.end());
        std::reverse(trail_edges.begin(), trail_edges.end());
        if (!trail_edges.empty()) trail_edges.erase(trail_edges.begin());

        if ((int)trail_edges.size() != (int)edges.size()) {
            trail_vertices.clear();
            trail_edges.clear();
            return false;
        }
        return true;
    }

    [[nodiscard]] const std::vector<int> &vertices() const { return trail_vertices; }
    [[nodiscard]] const std::vector<int> &edge_ids() const { return trail_edges; }
};
