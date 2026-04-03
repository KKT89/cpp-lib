#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

#include "data_structure/binary_trie.hpp"
#include "data_structure/union_find.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q;
    cin >> q;
    while (q--) {
        int n, m, K;
        cin >> n >> m >> K;
        UnionFind uf(n);
        vector<vector<pair<int, int>>> g(n);
        vector<tuple<int, int, int>> ex;
        for (int i = 0; i < m; ++i) {
            int x, y, z;
            cin >> x >> y >> z;
            x -= 1, y -= 1;
            if (!uf.same(x, y)) {
                uf.unite(x, y);
                g[x].emplace_back(y, z);
                g[y].emplace_back(x, z);
            } else {
                ex.emplace_back(x, y, z);
            }
        }

        vector<int> val(n);
        auto dfs = [&](auto self, int v, int p) -> void {
            for (auto [u, w] : g[v]) {
                if (u == p) continue;
                val[u] = val[v] ^ w;
                self(self, u, v);
            }
        };
        dfs(dfs, 0, -1);

        vector<int> base;
        for (auto [x, y, z] : ex) {
            int v = val[x] ^ val[y] ^ z;
            for (int b : base) {
                v = min(v, v ^ b);
            }
            if (v != 0) {
                for (int &b : base) {
                    b = min(b, b ^ v);
                }
                base.push_back(v);
            }
        }

        auto reduce = [&](int x) -> int {
            for (int b : base) {
                x = min(x, x ^ b);
            }
            return x;
        };

        ll res = 0;
        binary_trie<int, 30> trie;
        for (int i = 0; i < n; ++i) {
            int v = reduce(val[i]);
            res += trie.count_xor_leq(v, K);
            trie.insert(v);
        }
        cout << res << "\n";
    }
}