# Persistent Segment Tree

モノイド $(S, \text{op}, e)$ 上の永続セグメント木です。過去の任意のバージョンに対してクエリや更新を行います。

## Interface

```cpp
PersistentSegmentTree<S, op, e> seg(n);             // 長さ n, 全要素 e() で初期化 (version 0)
PersistentSegmentTree<S, op, e, 10000000> seg(n);   // 初期予約ノード数を指定 (デフォルト: 20000000)
PersistentSegmentTree<S, op, e> seg(v);             // vector v で初期化 (version 0)

int id = seg.set(root_id, k, x);                    // version root_id の位置 k を x に変更した新 version を作成
int id = seg.apply(root_id, k, x);                  // version root_id の位置 k に op(x, cur) を適用した新 version を作成
S x = seg.query(root_id, l, r);                     // version root_id の [l, r) の op 集約値を取得
S x = seg.get(root_id, k);                          // version root_id の位置 k の値を取得
int vc = seg.version_count();                       // 現在のバージョン数
```

## Notes

- `set(k, x)`, `apply(k, x)` は最新バージョンを元に新しいバージョンを作ります。過去のバージョンは変更しません。
- `POOL_SIZE` はノード数の上限ではなく、構築時の予約数です。超えるとプールを拡張します。
- 更新・取得は $O(\log n)$、更新ごとの追加領域は $O(\log n)$ です。
