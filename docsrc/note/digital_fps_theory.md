# デジタル冪級数 ~理論編~

## $m$-デジタル冪級数

### 定義

基数 $m \ge 2$ を1つ固定した時、
$$
f(x) = \prod_{k \ge 0} Q_{k}(x^{m^{k}})
$$
のように、ある多項式列 $\{ Q_{k}(x) \}^{\infty}_{k=0}$ が存在し、$Q_{k}(0) = 1 (k \ge 0)$ を満たす、形式的冪級数のことを指す。

### 例

$$
\frac{1}{1-x} = 1 + x + x^{2} + x^{3} + \cdots
$$
は二進数展開を考えることで、以下のように表現できることが分かる。

$$
\frac{1}{1-x} = (1 + x)(1 + x^{2})(1 + x^{4})(1 + x^{8}) \cdots
$$
従って、$Q_{k}(x) = (1 + x)$ とおくことで、$1 / (1 - x)$ は、2-デジタル冪級数であることが分かる。

## アルゴリズム (LSB-first)

任意の $m \ge 2$ と $t \in \{ 0, 1, \ldots, m-1 \}$ について、セクションオペレータ $S_{t, m}$ を
$$
S_{t, m} \left(\sum_{n \ge 0} a_{n} x^{n} \right) := \sum_{n \ge 0} a_{(nm+t)} x^{n}
$$
と定義する。特に $m=2$ の時は、偶数次と奇数次の項をそれぞれ取り出す、という操作に該当する。
$$
S_{0, 2}(f(x)) = a_0 + a_2 x + a_4 x^2 + \cdots
$$
$$
S_{1, 2}(f(x)) = a_1 + a_3 x + a_5 x^2 + \cdots
$$
以下、簡単のため $m=2$ に固定して考える[^1]。まず、任意の形式的冪級数 $f(x)$ について、
$$
[x^{N}]f(x) = [x^{\lfloor N/2 \rfloor}] S_{N \bmod{2}}(f(x))
$$
が成立する。ここで、2-デジタル冪級数 $B_{0}(x), B_{1}(x), \cdots$ が、形式的冪級数 $Q_{k}(x)$ を用いて、次のように表せるものとする。
$$
B_{n}(x) = \prod_{k \ge 0}Q_{n+k}(x^{2^{k}})
$$
この時、$S_{i}$ は、$\bmod{2}$ の値ごとに、$x$ の次数を $2$ で割っている操作であることに留意すると、 
$$
S_{i} (B_{n}(x)) = S_{i} (Q_{n}(x)) \prod_{k \ge 1}Q_{n+k}(x^{2^{k-1}})
= S_{i}(Q_{n}(x)) B_{n+1}(x)
$$
が得られる。同様に、形式的冪級数 $A(x)$ と $B_{n}(x)$ の積に対して、$S_{i}$ を作用させると、以下が成立する。
$$
S_{i} (A(x) B_{n}(x)) = S_{i} (A(x)Q_{n}(x)) \prod_{k \ge 1}Q_{n+k}(x^{2^{k-1}})
= S_{i}(A(x)Q_{n}(x)) B_{n+1}(x)
$$
以上より、2-デジタル冪級数 $\prod_{k \ge 0} Q_k(x^{2^k})$ が与えられた時、以下のアルゴリズムで $N$ 項目の係数を求めることができる。

```cpp
k <- 0
A <- 1
while N > 0 do
    A <- S(N % 2, A * Q_k)
    k <- k + 1
    N <- N / 2
end while
return A[0]
```
 
## Reference

- [桁dpを代数的にやっつける - Qiita](https://qiita.com/ryuhe1/items/185e1a283f13ac638a53)
- [Editorial - ABC300 Ex. Fibonacci: Revisited](https://atcoder.jp/contests/abc300/editorial/6269)

[^1]: 任意の $m$ に対しても、同様に成立する。