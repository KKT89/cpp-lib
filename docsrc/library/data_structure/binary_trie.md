# Binary Trie

整数の多重集合を管理し、XOR に関するクエリを高速に処理する Trie 木です。

## Interface

```cpp
BinaryTrie<T, LOG> bt;                // 空の集合で初期化 (T は整数型, LOG はビット幅)
bt.reserve(n);                        // 要素数が n になるまで追加する領域を確保
int n = bt.size();                    // 要素数
bt.insert(x);                         // x を追加
bt.erase(x);                          // x を1つ削除 (存在前提)
T x = bt[k];                          // k 番目 (0-indexed) に小さい値を取得
int cnt = bt.count_xor_leq(val, k);   // x XOR val <= k を満たす x の個数
int c = bt.cnt(idx);                  // idx を根とする部分木の要素数 (-1 なら 0)
auto [l, r] = bt.ch(idx);             // idx の 0 側と 1 側の子
int to = bt.ch(idx, bit);             // idx の bit 側の子
```

## Notes

- ノード番号は根を `0` とし、存在しない子を `-1` とします。
