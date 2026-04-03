# Binary Trie

整数の多重集合を管理し、XOR に関するクエリを高速に処理する Trie 木です。

## Interface

```cpp
binary_trie<T, LOG> bt;             // 空の集合で初期化 (T は整数型, LOG はビット幅)
bt.insert(x);                       // x を追加
bt.erase(x);                        // x を 1 つ削除 (存在前提)
int cnt = bt.count_xor_leq(val, k); // x XOR val <= k を満たす x の個数
```

| 操作 | 計算量 |
|------|--------|
| `insert(x)` | $O(\text{LOG})$ |
| `erase(x)` | $O(\text{LOG})$ |
| `count_xor_leq(val, k)` | $O(\text{LOG})$ |

## Code

```cpp
--8<-- "include/data_structure/binary_trie.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/data_structure/binary_trie.hpp"
```
