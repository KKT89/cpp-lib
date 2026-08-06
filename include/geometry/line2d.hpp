#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>
#include <iostream>

#include "geometry/point2d.hpp"

namespace geometry {

template <typename T>
struct Segment {
    std::array<Point<T>, 2> p{};

    Segment() = default;
    Segment(Point<T> a, Point<T> b) : p{a, b} {}

    Point<T>& operator[](int i) { return p[i]; }
    const Point<T>& operator[](int i) const { return p[i]; }

    Point<T> vec() const { return p[1] - p[0]; }

    T length() const
        requires std::floating_point<T>
    {
        return vec().length();
    }

    friend std::istream& operator>>(std::istream& is, Segment& s) {
        is >> s[0] >> s[1];
        return is;
    }
};

template <typename T>
Segment(Point<T>, Point<T>) -> Segment<T>;

template <typename T>
struct Line {
    std::array<Point<T>, 2> p{};

    Line() = default;
    Line(Point<T> a, Point<T> b) : p{a, b} {}
    Line(Segment<T> s) : p{s[0], s[1]} {}

    Point<T>& operator[](int i) { return p[i]; }
    const Point<T>& operator[](int i) const { return p[i]; }

    Point<T> vec() const { return p[1] - p[0]; }

    friend std::istream& operator>>(std::istream& is, Line& l) {
        is >> l[0] >> l[1];
        return is;
    }
};

template <typename T>
Line(Point<T>, Point<T>) -> Line<T>;

template <typename T>
Line(Segment<T>) -> Line<T>;

template <typename T>
bool is_parallel(const Line<T>& a, const Line<T>& b) {
    return sign(cross(a.vec(), b.vec())) == 0;
}

template <typename T>
bool is_orthogonal(const Line<T>& a, const Line<T>& b) {
    return sign(dot(a.vec(), b.vec())) == 0;
}

template <typename T>
bool intersects(const Segment<T>& a, const Segment<T>& b) {
    return ccw(a[0], a[1], b[0]) * ccw(a[0], a[1], b[1]) <= 0 && ccw(b[0], b[1], a[0]) * ccw(b[0], b[1], a[1]) <= 0;
}

template <Field T>
Point<T> projection(const Line<T>& l, const Point<T>& p) {
    Point<T> v = l.vec();
    return l[0] + v * (dot(p - l[0], v) / norm(v));
}

template <Field T>
Point<T> reflection(const Line<T>& l, const Point<T>& p) {
    return projection(l, p) * T(2) - p;
}

template <std::floating_point T>
T distance(const Line<T>& l, const Point<T>& p) {
    return std::abs(cross(l.vec(), p - l[0])) / l.vec().length();
}

template <std::floating_point T>
T distance(const Segment<T>& s, const Point<T>& p) {
    if (sign(dot(s[1] - s[0], p - s[0])) < 0) return dist(s[0], p);
    if (sign(dot(s[0] - s[1], p - s[1])) < 0) return dist(s[1], p);
    return distance(Line<T>(s), p);
}

template <std::floating_point T>
T distance(const Segment<T>& a, const Segment<T>& b) {
    if (intersects(a, b)) return T(0);
    return std::min({distance(a, b[0]), distance(a, b[1]), distance(b, a[0]), distance(b, a[1])});
}

template <Field T>
Point<T> crosspoint(const Line<T>& a, const Line<T>& b) {
    Point<T> va = a.vec();
    Point<T> vb = b.vec();
    return a[0] + va * (cross(vb, b[0] - a[0]) / cross(vb, va));
}

using S = Segment<Real>;
using L = Line<Real>;
using Si = Segment<long long>;
using Li = Line<long long>;

} // namespace geometry
