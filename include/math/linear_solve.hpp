#pragma once
#include <optional>
#include <utility>
#include <vector>

#include "math/gauss_jordan.hpp"

// 連立一次方程式ソルバー
// n: 変数の数 (x0, x1, ..., x_{n-1})
// solve(): 一意解が存在する場合は解ベクトルを返し、解なし・不定の場合は nullopt を返す
template <typename T>
struct LinearSystem {
    int n;
    std::vector<std::vector<T>> equations;

    explicit LinearSystem(int n) : n(n) {}

    // 密形式: 係数ベクトルをそのまま渡す
    void add(std::vector<T> coeffs, T rhs) {
        coeffs.push_back(rhs);
        equations.push_back(std::move(coeffs));
    }

    // 疎形式: 非ゼロ項を {変数インデックス, 係数} のペアで渡す
    void add(std::vector<std::pair<int, T>> terms, T rhs) {
        std::vector<T> coeffs(n, T{0});
        for (auto [idx, val] : terms) coeffs[idx] = val;
        coeffs.push_back(rhs);
        equations.push_back(std::move(coeffs));
    }

    std::optional<std::vector<T>> solve() const {
        auto mat = equations;
        if (gauss_jordan(mat) != n) return std::nullopt;
        std::vector<T> x(n);
        for (int i = 0; i < n; i++) x[i] = mat[i][n];
        return x;
    }
};
