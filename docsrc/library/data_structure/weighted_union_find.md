# 重み付き Union-Find

各要素に重みを持たせた Union-Find です。

## Interface

```cpp
WeightedUnionFind<T> uf(n);
bool ok  = uf.unite(x, y, w);   // weight(y) - weight(x) = w を課す (矛盾時 false)
bool con = uf.same(x, y);       // 同じ連結成分か
T    d   = uf.diff(x, y);       // weight(y) - weight(x)
T    w   = uf.weight(x);        // x の重み
int  s   = uf.size(x);          // x が属する連結成分のサイズ
int  r   = uf.find(x);          // x の根
```

