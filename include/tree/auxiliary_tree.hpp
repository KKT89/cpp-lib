#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "schieber_vishkin_lca.hpp"

struct AuxiliaryTree {
    const SchieberVishkinLCA *lca = nullptr;
    int n = 0;
    int root = -1;

    std::vector<int> depth;              // depth in original tree
    std::vector<int> preorder;           // preorder index (1..N)
    std::vector<std::vector<int>> g_aux; // directed: parent -> child (only valid for nodes in 'nodes')
    std::vector<int> nodes;              // nodes in current auxiliary tree (sorted by preorder)

    AuxiliaryTree() = default;
    explicit AuxiliaryTree(const SchieberVishkinLCA &l) { init(l); }

    // l.build(...) 済み
    void init(const SchieberVishkinLCA &l) {
        lca = &l;
        n = l.n;
        root = l.root;

        assert(n > 0);
        assert(0 <= root && root < n);
        assert((int)l.preorder.size() == n);

        depth.assign(n, 0);
        preorder.assign(n, 0);
        g_aux.assign(n, std::vector<int>());
        nodes.clear();

        for (int v = 0; v < n; ++v) {
            preorder[v] = (int)l.idx[v];
        }

        depth[root] = 0;
        for (int v : l.preorder) {
            if (v == root) continue;
            assert(0 <= l.par[v] && l.par[v] < n);
            depth[v] = depth[l.par[v]] + 1;
        }
    }

    // 前回 build の結果を軽量クリア（O(|nodes|)）
    void clear() {
        for (int v : nodes) {
            g_aux[v].clear();
        }
        nodes.clear();
    }

    // X から auxiliary tree を構築し、aux 木の根を返す
    // X は 0-index 頂点番号の配列（重複 OK）
    int build(std::vector<int> X) {
        clear();
        if (X.empty()) return -1;

        auto cmp = [&](int a, int b) { return preorder[a] < preorder[b]; };

        std::sort(X.begin(), X.end(), cmp);
        X.erase(std::unique(X.begin(), X.end()), X.end());

        // 性質2: 隣同士の LCA だけ追加
        int m = (int)X.size();
        std::vector<int> extra;
        extra.reserve(std::max(0, m - 1));
        for (int i = 0; i + 1 < m; ++i) {
            extra.push_back(lca->lca(X[i], X[i + 1]));
        }
        X.insert(X.end(), extra.begin(), extra.end());

        std::sort(X.begin(), X.end(), cmp);
        X.erase(std::unique(X.begin(), X.end()), X.end());

        nodes = X;

        std::vector<int> st;
        st.reserve(nodes.size());

        auto add_edge = [&](int p, int c) {
            g_aux[p].push_back(c); // parent -> child
        };

        st.push_back(nodes[0]);

        for (int i = 1; i < (int)nodes.size(); ++i) {
            int v = nodes[i];
            int w = lca->lca(v, st.back());

            if (w == st.back()) {
                st.push_back(v);
                continue;
            }

            while (st.size() >= 2 && depth[st[st.size() - 2]] >= depth[w]) {
                add_edge(st[st.size() - 2], st.back());
                st.pop_back();
            }

            if (st.back() != w) {
                add_edge(w, st.back());
                st.pop_back();
                if (st.empty() || st.back() != w) st.push_back(w);
            }

            st.push_back(v);
        }

        while (st.size() > 1) {
            add_edge(st[st.size() - 2], st.back());
            st.pop_back();
        }

        return st[0];
    }
};
