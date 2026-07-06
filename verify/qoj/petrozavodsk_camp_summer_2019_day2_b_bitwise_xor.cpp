#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "data_structure/binary_trie.hpp"
#include "math/static_modint_998244353.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    ll X;
    cin >> n >> X;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    binary_trie<ll, 60> bt;
    for (int i = 0; i < n; ++i) {
        bt.insert(a[i]);
    }

    vector<modint> po(n + 1);
    po[0] = 1;
    for (int i = 0; i < n; ++i) {
        po[i + 1] = po[i] + po[i];
    }

    auto nodes = bt.nodes;

    auto dfs2 = [&](auto dfs2, int cur1, int cur2, int bit) -> modint {
        int cnt1 = bt.cnt(cur1), cnt2 = bt.cnt(cur2);
        if (cnt1 == 0 or cnt2 == 0) {
            return 0;
        }
        if (bit < 0) {
            return modint(cnt1) * modint(cnt2);
        }
        int l1 = nodes[cur1].ch[0], r1 = nodes[cur1].ch[1];
        int l2 = nodes[cur2].ch[0], r2 = nodes[cur2].ch[1];
        int cnt_l1 = bt.cnt(l1), cnt_r1 = bt.cnt(r1);
        int cnt_l2 = bt.cnt(l2), cnt_r2 = bt.cnt(r2);
        int xb = (X >> bit) & 1;

        if (xb == 0) {
            modint res = 0;
            // このbitで1を立てたら即終了
            res += modint(cnt_l1) * modint(cnt_r2);
            res += modint(cnt_r1) * modint(cnt_l2);
            // 立たなかったら再帰継続
            res += dfs2(dfs2, l1, l2, bit - 1);
            res += dfs2(dfs2, r1, r2, bit - 1);
            return res;
        } else {
            return dfs2(dfs2, l1, r2, bit - 1) + dfs2(dfs2, r1, l2, bit - 1);
        }

        return 0;
    };

    auto dfs = [&](auto dfs, int cur, int bit) -> modint {
        int cnt = bt.cnt(cur);
        if (cur == -1 or bit < 0) {
            return po[cnt];
        }

        int l = nodes[cur].ch[0];
        int r = nodes[cur].ch[1];
        int xb = (X >> bit) & 1;

        if (xb == 0) {
            return dfs(dfs, l, bit - 1) * dfs(dfs, r, bit - 1);
        } else {
            // 空集合
            modint res = 1;
            // 1個だけ
            res += cnt;
            // 左右から1個ずつ
            res += dfs2(dfs2, l, r, bit - 1);
            return res;
        }
    };

    cout << dfs(dfs, 0, 59) - 1 << endl;
}
