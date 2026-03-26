#pragma once

#include <string>
#include <vector>

template <class Container>
std::vector<int> z_algorithm(const Container& s) {
    const int n = (int)s.size();
    std::vector<int> z(n, 0);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i < r) z[i] = std::min(z[i - l], r - i);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i] += 1;
        }
        if (r < i + z[i]) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
