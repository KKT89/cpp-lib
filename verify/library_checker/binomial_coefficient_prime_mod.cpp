#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#include "math/combination.hpp"
#include "math/dynamic_modint.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int q, mod;
    cin >> q >> mod;
    using modint = dynamic_modint<0>;
    modint::set_mod(mod);
    constexpr int N = 1e7;
    Combination<modint, N> comb;

    while (q--) {
        int n, k;
        cin >> n >> k;
        cout << comb.comb(n, k) << "\n";
    }
}
