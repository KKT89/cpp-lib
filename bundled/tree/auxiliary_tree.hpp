// bundled by scripts/bundle_header.py

// ---- begin: include/tree/auxiliary_tree.hpp

#include <algorithm>
#include <vector>

// ---- begin: include/tree/schieber_vishkin_lca.hpp

#include <algorithm>
#include <bit>
#include <vector>

struct SchieberVishkinLCA {
    using uint = unsigned int;

    static uint lowbit(uint x) { return x & (~x + 1); }
    static uint msb_minus_1_mask(uint x) { return std::bit_floor(x | 1u) - 1u; }

    int n;
    int root = -1;
    std::vector<std::vector<int>> g;
    std::vector<int> ord, par;
    std::vector<uint> idx, inlabel, ascendant;
    std::vector<int> head;

    explicit SchieberVishkinLCA(int n = 0) : n(n), g(n), par(n, -1), idx(n, 0) { ord.reserve(n); }

    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // build: O(N), query: O(1)
    void build(int r = 0) {
        if (n == 0) return;

        ord.clear();
        std::fill(par.begin(), par.end(), -1);
        root = r;

        std::vector<int> st;
        st.reserve(n);
        st.push_back(r);
        par[r] = -1;

        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            ord.push_back(v);
            for (int i = (int)g[v].size() - 1; i >= 0; --i) {
                int to = g[v][i];
                if (to == par[v]) continue;
                par[to] = v;
                st.push_back(to);
            }
        }

        for (int i = 0; i < n; ++i) {
            idx[ord[i]] = (uint)(i + 1);
        }

        inlabel = idx;
        for (int i = n - 1; i > 0; --i) {
            int v = ord[i];
            int p = par[v];
            if (lowbit(inlabel[p]) < lowbit(inlabel[v])) inlabel[p] = inlabel[v];
        }

        ascendant.assign(n, 0);
        head.assign(n, 0);

        ascendant[r] = 0;
        head[0] = r;

        for (int i = 1; i < n; ++i) {
            int v = ord[i];
            int p = par[v];
            ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
        }
        for (int i = 1; i < n; ++i) {
            int v = ord[i];
            int p = par[v];
            if (inlabel[v] != inlabel[p]) {
                head[idx[v] - 1] = p;
            } else {
                head[idx[v] - 1] = head[idx[p] - 1];
            }
        }
    }

    int lca(int u, int v) const {
        uint Iv = inlabel[v];
        uint Iu = inlabel[u];
        uint hIv = lowbit(Iv);
        uint hIu = lowbit(Iu);
        uint mask = msb_minus_1_mask((Iv ^ Iu) | hIv | hIu);
        uint j = lowbit(ascendant[v] & ascendant[u] & ~mask);

        int x, y;
        if (j == hIv) {
            x = v;
        } else {
            mask = msb_minus_1_mask(ascendant[v] & (j - 1));
            x = head[(idx[v] & ~mask | (mask + 1)) - 1];
        }
        if (j == hIu) {
            y = u;
        } else {
            mask = msb_minus_1_mask(ascendant[u] & (j - 1));
            y = head[(idx[u] & ~mask | (mask + 1)) - 1];
        }
        return idx[x] < idx[y] ? x : y;
    }
};
// ---- end: include/tree/schieber_vishkin_lca.hpp

struct AuxiliaryTree {
    const SchieberVishkinLCA* lca = nullptr;
    int n = 0;
    int root = -1;

    std::vector<int> depth;          // depth in original tree
    std::vector<int> tin;            // preorder index (1..N)
    std::vector<std::vector<int>> g_aux;  // directed: parent -> child (only valid for nodes in 'nodes')
    std::vector<int> nodes;          // nodes in current auxiliary tree (sorted by tin)

    AuxiliaryTree() = default;
    explicit AuxiliaryTree(const SchieberVishkinLCA& l, int r = -1) { init(l, r); }

    // l.build(root) 済み前提
    void init(const SchieberVishkinLCA& l, int r = -1) {
        lca = &l;
        n = l.n;
        root = (r >= 0 ? r : l.root);
        if (root < 0) root = 0;

        depth.assign(n, 0);
        tin.assign(n, 0);
        g_aux.assign(n, std::vector<int>());
        nodes.clear();

        for (int v = 0; v < n; ++v) tin[v] = (int)l.idx[v];

        depth[root] = 0;
        for (int v : l.ord) {
            if (v == root) continue;
            depth[v] = depth[l.par[v]] + 1;
        }
    }

    // 前回 build の結果を軽量クリア（O(|nodes|)）
    void clear() {
        for (int v : nodes) g_aux[v].clear();
        nodes.clear();
    }

    // X から auxiliary tree を構築し、aux 木の根を返す
    // X は 0-index 頂点番号の配列（重複 OK）
    int build(std::vector<int> X) {
        clear();
        if (X.empty()) return -1;

        auto cmp = [&](int a, int b) { return tin[a] < tin[b]; };

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
            g_aux[p].push_back(c);  // parent -> child
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
// ---- end: include/tree/auxiliary_tree.hpp
