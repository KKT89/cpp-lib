#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "data_structure/range_affine_point_get.hpp"
#include "math/static_modint_998244353.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    vector<modint> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    RangeAffinePointGet<modint> seg(a);
    while (q--) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, b, c);
        } else {
            int idx;
            cin >> idx;
            cout << seg.get(idx) << "\n";
        }
    }
}
