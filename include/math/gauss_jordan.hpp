#pragma once
#include <cmath>
#include <type_traits>
#include <vector>

template <typename T>
int gauss_jordan(std::vector<std::vector<T>> &A, bool augmented = true) {
    using std::abs;
    T eps;
    if constexpr (std::is_floating_point_v<T>) {
        eps = T{1e-10};
    } else {
        eps = T{0};
    }
    int n = A.size(), m = A[0].size();
    int rank = 0;
    int col_limit = augmented ? m - 1 : m;
    for (int col = 0; col < col_limit; col++) {
        int pivot = -1;
        T max_val = eps;
        for (int row = rank; row < n; row++) {
            if (abs(A[row][col]) > max_val) {
                max_val = abs(A[row][col]);
                pivot = row;
            }
        }
        if (pivot == -1) continue;
        std::swap(A[pivot], A[rank]);
        T fac = A[rank][col];
        for (int j = 0; j < m; j++) {
            A[rank][j] /= fac;
        }
        for (int row = 0; row < n; row++) {
            if (row != rank && abs(A[row][col]) > eps) {
                T fac = A[row][col];
                for (int j = 0; j < m; j++) {
                    A[row][j] -= A[rank][j] * fac;
                }
            }
        }
        rank++;
    }
    return rank;
}
