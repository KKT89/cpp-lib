# Z Algorithm

文字列（または任意の列） `s` に対して、`s` と `s[i..]` の最長共通接頭辞の長さを求めます。

$$
z[i] = \max \{ k \mid s[0..k) = s[i..i+k) \}, \quad z[0] = n
$$

## Interface

```cpp
vector<int> z = z_algorithm(s);   // std::string
vector<int> z = z_algorithm(v);   // std::vector<T>
```
