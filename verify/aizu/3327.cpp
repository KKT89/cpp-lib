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

    WeightedUnionFind<ll> uf(n);

    bool ok = true;
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < n; k++) {
            // (x_i - x_0) + (y_{i+k} - y_k) = a[i][i+k] - a[0][k]
            // (x_i - x_0) + (y_{i+k+1} - y_{k+1}) = a[i][i+k+1] - a[0][k+1]
            int y1 = k, y2 = (i + k) % n, y3 = (k + 1) % n, y4 = (i + k + 1) % n;
            ll diff = (a[i][y4] - a[0][y3]) - (a[i][y2] - a[0][y1]);
            // (y_{i+k+1} - y_{i+k}) - (y_{k+1} - y_k) = diff
            if (!uf.unite(y1, y2, diff)) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    // ポテンシャルの総和は0
    // 適当な基準をとって、n*x + sum = 0 と書けることを利用して、整数解のチェックを行う
    ll sum = 0;
    for (int i = 0; i < n; i++) {
        sum += uf.weight(i);
    }

    cout << (sum % n == 0 ? "Yes" : "No") << endl;
}