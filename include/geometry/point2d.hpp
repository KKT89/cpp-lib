#pragma once

#include <cmath>
#include <concepts>
#include <iostream>

#include "geometry/geometry_base.hpp"

namespace geometry {

inline constexpr int COUNTER_CLOCKWISE = 1;
inline constexpr int CLOCKWISE = -1;
inline constexpr int ONLINE_BACK = 2;
inline constexpr int ONLINE_FRONT = -2;
inline constexpr int ON_SEGMENT = 0;

template <typename T>
struct Point {
    T x{}, y{};

    Point() = default;
    Point(T x, T y) : x(x), y(y) {}

    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }

    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }

    Point& operator*=(const T& k) {
        x *= k;
        y *= k;
        return *this;
    }

    Point& operator/=(const T& k) {
        x /= k;
        y /= k;
        return *this;
    }

    Point operator+() const { return *this; }
    Point operator-() const { return {-x, -y}; }

    friend Point operator+(Point a, const Point& b) { return a += b; }
    friend Point operator-(Point a, const Point& b) { return a -= b; }
    friend Point operator*(Point p, const T& k) { return p *= k; }
    friend Point operator*(const T& k, Point p) { return p *= k; }
    friend Point operator/(Point p, const T& k) { return p /= k; }

    friend bool operator<(const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    }

    friend bool operator==(const Point& a, const Point& b) { return a.x == b.x && a.y == b.y; }
    friend bool operator!=(const Point& a, const Point& b) { return !(a == b); }

    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& p) { return os << p.x << ' ' << p.y; }

    auto norm() const {
        using W = calc_t<T>;
        return W(x) * x + W(y) * y;
    }

    T length() const
        requires std::floating_point<T>
    {
        return safe_sqrt(norm());
    }

    Point unit() const
        requires std::floating_point<T>
    {
        return *this / length();
    }

    Point rotate(T theta) const
        requires std::floating_point<T>
    {
        T c = std::cos(theta);
        T s = std::sin(theta);
        return {x * c - y * s, x * s + y * c};
    }

    Point perpendicular() const { return {-y, x}; }

    Point normal() const
        requires std::floating_point<T>
    {
        return perpendicular().unit();
    }
};

template <typename T>
bool equals(const Point<T>& a, const Point<T>& b) {
    return sign(a.x, b.x) == 0 && sign(a.y, b.y) == 0;
}

template <typename T>
Point<T> vec(const Point<T>& a, const Point<T>& b) {
    return b - a;
}

template <typename T>
auto dot(const Point<T>& a, const Point<T>& b) {
    using W = calc_t<T>;
    return W(a.x) * b.x + W(a.y) * b.y;
}

template <typename T>
auto cross(const Point<T>& a, const Point<T>& b) {
    using W = calc_t<T>;
    return W(a.x) * b.y - W(a.y) * b.x;
}

template <typename T>
auto norm(const Point<T>& p) {
    return p.norm();
}

template <std::floating_point T>
T length(const Point<T>& p) {
    return p.length();
}

template <std::floating_point T>
T dist(const Point<T>& a, const Point<T>& b) {
    return (b - a).length();
}

template <typename T>
int ccw(Point<T> a, Point<T> b, Point<T> c) {
    b -= a;
    c -= a;
    if (sign(cross(b, c)) > 0) return COUNTER_CLOCKWISE;
    if (sign(cross(b, c)) < 0) return CLOCKWISE;
    if (sign(dot(b, c)) < 0) return ONLINE_BACK;
    if (sign(c.norm(), b.norm()) > 0) return ONLINE_FRONT;
    return ON_SEGMENT;
}

using P = Point<Real>;
using Pi = Point<long long>;

} // namespace geometry
