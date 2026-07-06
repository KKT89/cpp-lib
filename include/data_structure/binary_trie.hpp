#pragma once
#include <array>
#include <cassert>
#include <vector>

template <class T, int LOG>
struct binary_trie {
    struct node {
        int cnt = 0;
        std::array<int, 2> ch = {-1, -1};
    };
    std::vector<node> nodes;

    binary_trie() { nodes.emplace_back(); }

    int size() const { return nodes[0].cnt; }

    // ノード idx を根とする部分木の要素数
    int cnt(int idx) const { return idx == -1 ? 0 : nodes[idx].cnt; }

    void insert(T x) {
        int cur = 0;
        nodes[cur].cnt += 1;
        for (int i = LOG - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (nodes[cur].ch[b] == -1) {
                nodes[cur].ch[b] = (int)nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].ch[b];
            nodes[cur].cnt += 1;
        }
    }

    void erase(T x) {
        int cur = 0;
        nodes[cur].cnt -= 1;
        for (int i = LOG - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            cur = nodes[cur].ch[b];
            nodes[cur].cnt -= 1;
        }
    }

    T operator[](int k) const {
        assert(0 <= k && k < size());
        int cur = 0;
        T x = 0;
        for (int i = LOG - 1; i >= 0; --i) {
            int left = nodes[cur].ch[0];
            int left_cnt = cnt(left);
            if (k < left_cnt) {
                cur = left;
            } else {
                k -= left_cnt;
                cur = nodes[cur].ch[1];
                x |= (T(1) << i);
            }
        }
        return x;
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
                res += cnt(nodes[cur].ch[vb]);
                cur = nodes[cur].ch[vb ^ 1];
            } else {
                cur = nodes[cur].ch[vb];
            }
        }
        res += cnt(cur);
        return res;
    }
};
