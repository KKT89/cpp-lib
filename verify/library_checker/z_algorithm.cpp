#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

#include "string/z_algorithm.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    auto Z = z_algorithm(s);
    for (int i = 0; i < s.size(); ++i) {
        cout << Z[i] << " ";
    }
    cout << endl;
}