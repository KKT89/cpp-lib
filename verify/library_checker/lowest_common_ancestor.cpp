#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "tree/lowest_common_ancestor.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    LowestCommonAncestor lca(n);
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        lca.add_edge(i, p);
    }
    lca.build(0);

    while (q--) {
        int u, v;
        cin >> u >> v;
        cout << lca.lca(u, v) << '\n';
    }
    return 0;
}
