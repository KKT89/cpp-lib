#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#include "graph/weighted_union_find.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector a(n, vector<ll>(n));
    vector b(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> b[i][j];
            a[i][j] = b[i][j] - a[i][j];
        }
    }

    WeightedUnionFind<ll> uf(2 * n);

    for (int k = 0; k < n; ++k) {
        for (int x = 1; x < n; ++x) {
            int y = (x + k) % n;
            auto f = uf.unite(x, n + y, a[x][y] - a[0][k]);
            if (!f) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
}