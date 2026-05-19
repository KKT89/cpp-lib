# Persistent Segment Tree

モノイド $(S, \text{op}, e)$ 上の永続セグメント木です。過去の任意のバージョンに対してクエリや更新を行えます。

## Interface

```cpp
persistent_segtree<S, op, e> seg(n);             // 長さ n, 全要素 e() で初期化 (version 0)
persistent_segtree<S, op, e, 10000000> seg(n);   // プールサイズを指定 (デフォルト: 20000000)
persistent_segtree<S, op, e> seg(v);             // vector v で初期化 (version 0)

int id = seg.set(k, x, root_id);                 // version root_id の位置 k を x に変更した新 version を作成
int id = seg.apply(k, x, root_id);               // version root_id の位置 k に op(x, cur) を適用した新 version を作成
S x = seg.query(root_id, l, r);                  // version root_id の [l, r) の op 集約値を取得
S x = seg.get(root_id, k);                       // version root_id の位置 k の値を取得
int vc = seg.version_count();                    // 現在のバージョン数
```

`set`, `apply` の `root_id` を省略すると最新バージョンを使用します。
