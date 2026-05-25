# 中国剰余定理

中国剰余定理 (CRT) の拡張版です。法が互いに素でない場合も正しく動作します。

## Interface

```cpp
vector<long long> r = {2, 3, 2};   // x = 23, lcm = 105
vector<long long> m = {3, 5, 7};   // 23 ≡ 2 (mod 3), 23 ≡ 3 (mod 5), 23 ≡ 2 (mod 7)
auto [x, lcm] = crt(r, m);         // O(n log lcm)
```

## Notes

- `m[i] >= 1` を仮定します。
- 解が存在しないとき `{0, 0}`、空入力のとき `{0, 1}` を返します。
- 返り値の `x` は最小の非負解です。
- 法は `long long` に収まる範囲を想定します。
