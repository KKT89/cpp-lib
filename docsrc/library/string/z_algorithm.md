---
tags:
  - string
  - z_algorithm
---

# Z Algorithm

文字列（または任意の列） `s` に対して、`s` と `s[i..]` の最長共通接頭辞の長さを
全インデックスについて O(n) で求める実装です。

$$
z[i] = \max \{ k \mid s[0..k) = s[i..i+k) \}, \quad z[0] = n
$$

## Interface

```cpp
// std::string
std::vector<int> z = z_algorithm(s);

// std::vector<T>
std::vector<int> z = z_algorithm(v);
```

| 操作 | 計算量 |
|------|--------|
| `z_algorithm(s)` | $O(n)$ |

## Code

```cpp
--8<-- "include/string/z_algorithm.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/string/z_algorithm.hpp"
```
