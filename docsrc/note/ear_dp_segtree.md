# 耳DPをセグメント木に載せる

各区間に、開始状態と終了状態ごとの最大増分を持つ。区間の答えだけでは、左区間から右区間へ途中の状態を引き継げない。

## DPから遷移行列を作る

まず、1 要素を読む処理を旧 `dp` から新 `ndp` への更新として書く。状態数を $K$ とし、遷移が

$$
\mathrm{ndp}[j] = \max_i \bigl(\mathrm{dp}[i] + M[i][j]\bigr)
$$

の形なら、$M[i][j]$ は状態 $i$ から $j$ への最大増分を表す。行が開始状態、列が終了状態。遷移できない組は $-\infty$ とする。この演算は [max-plus 行列](https://info.atcoder.jp/entry/algorithm_lectures/range_query_monoid_design)として扱える。

左区間 $L$、右区間 $R$ をこの順に読むと、境界の状態 $j$ を経由するので

$$
\operatorname{op}(L,R)[i][k] = \max_j \bigl(L[i][j] + R[j][k]\bigr)
$$

となる。空区間は状態を変えず、得点も増やさないため、単位元は対角 $0$、それ以外 $-\infty$。

初期 DP が状態 $s$ のみ $0$、他は $-\infty$ なら、区間を読んだ結果は $M[s][j]$。答えは、許される終了状態 $j$ の中から取る。

この行列を [Segment Tree](../library/segtree/segtree.md) の `S` にし、`op` を行列積、`e()` を単位行列にする。一般の $K$ 状態なら、更新・区間取得は $O(K^3 \log n)$。状態番号が減らない場合は、結合の計算を $i \le j \le k$ に絞れる。

## 例 高々2個の連続区間を選ぶ

[AAL Contest 001 I 連続部分列](https://atcoder.jp/contests/aalc001/tasks/aalc001_i)では、重ならない非空の連続区間を 0〜2 個選び、合計を最大化する。

| 状態 | 意味 |
| --- | --- |
| 0 | まだ選んでいない |
| 1 | 1 個目の区間の中 |
| 2 | 1 個目を終え、選んでいない |
| 3 | 2 個目の区間の中 |
| 4 | 2 個目を終えた |

現在の要素を $x$ とすると、1 要素分の更新は次の通り。右辺はすべて更新前の値を使う。

$$
\begin{aligned}
d'_0 &= d_0, \\
d'_1 &= \max(d_0,d_1)+x, \\
d'_2 &= \max(d_1,d_2), \\
d'_3 &= \max(d_2,d_3)+x, \\
d'_4 &= \max(d_3,d_4).
\end{aligned}
$$

したがって、葉に置く行列は

$$
M(x)=
\begin{pmatrix}
0 & x & -\infty & -\infty & -\infty \\
-\infty & x & 0 & -\infty & -\infty \\
-\infty & -\infty & 0 & x & -\infty \\
-\infty & -\infty & -\infty & x & 0 \\
-\infty & -\infty & -\infty & -\infty & 0
\end{pmatrix}.
$$

$1\to2$ と $3\to4$ は、現在の要素を選ばずに読む遷移。隣り合う 2 区間は 1 区間にまとめられるため、この問題では $1\to3$ を用意しなくてもよい。

初期値は $(0,-\infty,-\infty,-\infty,-\infty)$。区間を選んでいる途中で読み終えてもよく、0 個の選択も許すので、答えは

$$
\max_{j=0}^4 M[0][j].
$$

例えば列が `[5]` なら、$M[0][1]=5$ だが $M[0][4]=-\infty$。終了状態を 4 に固定すると答えを取れない。

## 実装

状態番号が減らない最大化DP用。`op` と `e()` は使い回し、状態数・`make_leaf`・初期状態・終了状態を問題に合わせる。

```cpp
#include "segtree/segtree.hpp"

constexpr int K = 5;
constexpr ll NEG = -(1LL << 60);
using S = array<array<ll, K>, K>;

S e() {
    S m;
    for (int i = 0; i < K; ++i) {
        m[i].fill(NEG);
        m[i][i] = 0;
    }
    return m;
}

S op(S a, S b) {
    S c;
    for (auto& row : c) {
        row.fill(NEG);
    }
    for (int i = 0; i < K; ++i) {
        for (int j = i; j < K; ++j) {
            if (a[i][j] == NEG) continue;
            for (int k = j; k < K; ++k) {
                if (b[j][k] == NEG) continue;
                c[i][k] = max(c[i][k], a[i][j] + b[j][k]);
            }
        }
    }
    return c;
}

S make_leaf(ll x) {
    S m = e();
    m[1][1] = m[3][3] = x;
    m[0][1] = m[2][3] = x;
    m[1][2] = m[3][4] = 0;
    return m;
}

using Seg = SegmentTree<S, op, e>;
```

入力列 `a` から構築し、点更新にも同じ `make_leaf` を使う。この例は初期状態が 0 で、すべての終了状態を許す。

```cpp
vector<S> v(a.size());
for (int i = 0; i < (int)a.size(); ++i) {
    v[i] = make_leaf(a[i]);
}
Seg seg(v);
seg.set(i, make_leaf(x));
S m = seg.query(l, r);
ll ans = *max_element(m[0].begin(), m[0].end());
```

状態番号が戻る遷移もある場合は、`op` の添字 $i,j,k$ をすべて $0\le i,j,k<K$ に広げる。

## 実装で混ぜないこと

- **1 要素分の更新と状態の切り替え。** in-place の DP は旧 `dp` から `ndp` への式に直す。同じ要素を二度加算する遷移を作らない。
- **空区間と無料の状態移動。** 全成分 $0$ の行列は、任意の状態へ無料で移る作用であり、単位元ではない。単位元を直すときは、葉と終了状態も同じ DP の定義に揃える。
- **単位元と積の初期値。** `op` の結果は全成分 `NEG` で初期化する。`e()` から始めると、負の対角値を勝手に 0 に変えてしまう。
- **到達不能と小さい有限値。** `NEG` は到達可能な値より小さくし、有限値の和は `ll` に収める。行列積では `NEG` を含む加算を飛ばし、`NEG + x` を到達可能な値として扱わない。
