#pragma once
#include <array>
#include <vector>

template <class T, int LOG> struct binary_trie {
    struct node {
        int cnt = 0;
        std::array<int, 2> ch = {-1, -1};
    };
    std::vector<node> nodes;

    binary_trie() { nodes.emplace_back(); }

    void insert(T x) {
        int cur = 0;
        nodes[cur].cnt++;
        for (int i = LOG - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (nodes[cur].ch[b] == -1) {
                nodes[cur].ch[b] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].ch[b];
            nodes[cur].cnt++;
        }
    }

    void erase(T x) {
        int cur = 0;
        nodes[cur].cnt--;
        for (int i = LOG - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            cur = nodes[cur].ch[b];
            nodes[cur].cnt--;
        }
    }

    // x XOR val <= k となる整数 x の個数
    int count_xor_leq(T val, T k) {
        int cur = 0;
        int res = 0;
        for (int i = LOG - 1; i >= 0; --i) {
            if (cur == -1) break;
            int vb = (val >> i) & 1;
            int kb = (k >> i) & 1;
            if (kb == 1) {
                int c = nodes[cur].ch[vb];
                if (c != -1) res += nodes[c].cnt;
                cur = nodes[cur].ch[vb ^ 1];
            } else {
                cur = nodes[cur].ch[vb];
            }
        }
        if (cur != -1) res += nodes[cur].cnt;
        return res;
    }
};
