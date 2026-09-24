# Z Algorithm

文字列（または任意の列） `s` に対して、`s` と `s[i..]` の最長共通接頭辞の長さを求めます。

$$
z[i] = \max \{ k \mid s[0..k) = s[i..i+k) \}, \quad z[0] = n
$$

## Interface

```cpp
vector<int> z = z_algorithm(s);   // std::string, O(n)
vector<int> z = z_algorithm(v);   // std::vector<T>, O(n)
```

## Notes

- 入力は空でない列とし、要素同士を `==` で比較できることを仮定します。
