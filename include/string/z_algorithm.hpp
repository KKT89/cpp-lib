#pragma once

#include <string>
#include <vector>

/// @brief Z アルゴリズム
///
/// z[i] = s と s[i..] の最長共通接頭辞の長さ（z[0] = n）を O(n) で求める。
/// std::string / std::vector<T> の両方に対応。
///
/// @param s  入力列
/// @return   z 配列（長さ n、z[0] = n）
template <class Container>
std::vector<int> z_algorithm(const Container& s) {
    const int n = (int)s.size();
    std::vector<int> z(n, 0);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = std::min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
