#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <type_traits>

namespace geometry {

using Real = double;
inline Real EPS = 1e-8; // 許容誤差

template <typename T>
int sign(const T& x) {
    if constexpr (std::floating_point<T>) {
        return x < -EPS ? -1 : x > EPS ? 1 : 0;
    } else {
        return (x > T(0)) - (x < T(0));
    }
}

template <typename T>
int sign(const T& a, const T& b) {
    return sign(a - b);
}

template <typename T>
int sgn(const T& x) {
    return sign(x);
}

template <typename T>
int sgn(const T& a, const T& b) {
    return sign(a, b);
}

template <std::floating_point T>
T safe_sqrt(T x) {
    return std::sqrt(std::max(x, T(0)));
}

// 内部計算用の型: 整数型は桁溢れを防ぐため __int128_t に広げる。
template <typename T>
using calc_t = std::conditional_t<std::is_integral_v<T>, __int128_t, T>;

// 整数型は切り捨て除算で誤るため除外する。
template <typename T>
concept Field = !std::is_integral_v<T> && requires(T a, T b) {
    { a / b };
};

} // namespace geometry
