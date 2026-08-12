#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;

#include "data_structure/range_tree.hpp"

using S = ll;
S op(S x, S y) { return x + y; }
S e() { return 0; }

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    RangeTree<S, op, e, int> tree;

    vector<int> x(n), y(n), z(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i] >> z[i];
        tree.add_point(x[i], y[i]);
    }
    vector<int> type(q);
    vector<int> l(q), d(q), r(q), u(q);
    for (int i = 0; i < q; ++i) {
        cin >> type[i];
        if (type[i] == 0) {
            cin >> l[i] >> d[i] >> r[i];
            tree.add_point(l[i], d[i]);
        } else {
            cin >> l[i] >> d[i] >> r[i] >> u[i];
        }
    }
    tree.build();
    for (int i = 0; i < n; ++i) {
        tree.add(x[i], y[i], z[i]);
    }
    for (int i = 0; i < q; ++i) {
        if (type[i] == 0) {
            tree.add(l[i], d[i], r[i]);
        } else {
            cout << tree.prod(l[i], r[i], d[i], u[i]) << "\n";
        }
    }
}
