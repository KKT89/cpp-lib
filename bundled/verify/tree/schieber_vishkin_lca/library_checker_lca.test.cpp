// bundled by scripts/bundle_header.py

// ---- begin: verify/tree/schieber_vishkin_lca/library_checker_lca.test.cpp
#include <iostream>

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
    std::vector<int> preorder, par;
    std::vector<uint> idx, inlabel, ascendant;
    std::vector<int> head;

    explicit SchieberVishkinLCA(int n = 0) : n(n), g(n), par(n, -1), idx(n, 0) { preorder.reserve(n); }

    void add_edge(int x, int y) {
        g[x].push_back(y);
        g[y].push_back(x);
    }

    // build: O(N), query: O(1)
    void build(int r = 0) {
        if (n == 0) return;

        preorder.clear();
        std::fill(par.begin(), par.end(), -1);
        root = r;

        std::vector<int> st;
        st.reserve(n);
        st.push_back(r);
        par[r] = -1;

        while (!st.empty()) {
            int v = st.back();
            st.pop_back();
            preorder.push_back(v);
            for (int i = (int)g[v].size() - 1; i >= 0; --i) {
                int to = g[v][i];
                if (to == par[v]) continue;
                par[to] = v;
                st.push_back(to);
            }
        }

        for (int i = 0; i < n; ++i) {
            idx[preorder[i]] = (uint)(i + 1);
        }

        inlabel = idx;
        for (int i = n - 1; i > 0; --i) {
            int v = preorder[i];
            int p = par[v];
            if (lowbit(inlabel[p]) < lowbit(inlabel[v])) inlabel[p] = inlabel[v];
        }

        ascendant.assign(n, 0);
        head.assign(n, 0);

        ascendant[r] = 0;
        head[0] = r;

        for (int i = 1; i < n; ++i) {
            int v = preorder[i];
            int p = par[v];
            ascendant[v] = ascendant[p] | lowbit(inlabel[v]);
        }
        for (int i = 1; i < n; ++i) {
            int v = preorder[i];
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    SchieberVishkinLCA lca(n);
    for (int i = 1; i < n; ++i) {
        int p;
        std::cin >> p;
        lca.add_edge(i, p);
    }
    lca.build(0);

    while (q--) {
        int u, v;
        std::cin >> u >> v;
        std::cout << lca.lca(u, v) << '\n';
    }
    return 0;
}
// ---- end: verify/tree/schieber_vishkin_lca/library_checker_lca.test.cpp
