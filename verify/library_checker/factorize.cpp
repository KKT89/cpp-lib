#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;

#include "math/factorize.hpp"

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;
        auto vs = factorize::prime_factor(n);
        cout << vs.size();
        for (auto p : vs) {
            cout << " " << p;
        }
        cout << "\n";
    }
}