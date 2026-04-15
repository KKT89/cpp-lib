# 中国剰余定理

中国剰余定理 (CRT) の拡張版です。法が互いに素でなくても正しく動作します。

## Interface

```cpp
#include "math/crt.hpp"

vector<long long> r = {2, 3, 2};
vector<long long> m = {3, 5, 7};
auto [x, lcm] = crt(r, m);
// x = 23, lcm = 105
// 23 ≡ 2 (mod 3), 23 ≡ 3 (mod 5), 23 ≡ 2 (mod 7)
```

| 操作 | 計算量 |
|------|--------|
| `crt(r, m)` | $O(n \log \mathrm{lcm})$ |

## Notes

- `m[i] >= 1` が必要です。
- `r[i]` は負の値でも OK です。
- 解が存在しないとき `{0, 0}` を返します。
- 入力が空のとき `{0, 1}` を返します。
- 答えの法 (各 `m[i]` の lcm) が `long long` に収まる必要があります。
- 法が互いに素でない場合も正しく処理します（拡張 CRT）。

## Code

```cpp
--8<-- "include/math/crt.hpp"
```

## Bundled (Copy & Paste)

```cpp
--8<-- "bundled/math/crt.hpp"
```
