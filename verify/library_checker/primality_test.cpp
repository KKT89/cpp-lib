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
        if (factorize::is_prime(n)) {
            cout << "Yes" << "\n";
        } else {
            cout << "No" << "\n";
        }
    }
}