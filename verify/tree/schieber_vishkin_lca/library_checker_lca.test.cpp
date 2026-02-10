#include <iostream>

#include "../../../include/tree/schieber_vishkin_lca.hpp"

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
