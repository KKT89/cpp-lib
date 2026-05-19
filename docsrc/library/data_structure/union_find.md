# Union-Find

グループ分けを効率的に管理する、根付き木を用いたデータ構造です。

## Interface

```cpp
UnionFind uf(n);          // n 頂点で初期化
uf.unite(u, v);           // u と v を併合
bool b = uf.same(u, v);   // u と v が同じ連結成分か
int s = uf.size(v);       // v の属する連結成分のサイズ
int r = uf.find(v);       // v の根を取得
```

