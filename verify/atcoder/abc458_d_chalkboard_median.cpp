#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "data_structure/binary_trie.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x;
    cin >> x;
    binary_trie<int, 30> bt;
    bt.insert(x);
    int q;
    cin >> q;
    while (q--) {
        int a, b;
        cin >> a >> b;
        bt.insert(a);
        bt.insert(b);
        cout << bt[(bt.size() - 1) / 2] << "\n";
    }
}
