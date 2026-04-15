#include <bits/stdc++.h>
#include "data_structure/persistent_segtree.hpp"
using namespace std;
typedef long long ll;

ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;

    persistent_segtree<ll, op, e> seg(m);
    vector<int> root(n, 0);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x -= 1, y -= 1;
            root[x] = root[y];
        } else if (t == 2) {
            int x, y, z;
            cin >> x >> y >> z;
            x -= 1, y -= 1;
            root[x] = seg.set(y, z, root[x]);
        } else {
            int x, l, r;
            cin >> x >> l >> r;
            x -= 1, l -= 1;
            cout << seg.query(root[x], l, r) << "\n";
        }
    }
}
