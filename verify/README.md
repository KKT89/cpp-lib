# verify 方針（暫定）

- verify コードは `verify/<category>/<library_name>/` に置く。
- 1ライブラリに対して複数ジャッジの verify を並べる。
  - 例: `library_checker_lca.test.cpp`, `atcoder_abc014_d.test.cpp`
- verify コードは `include/...` のライブラリを `#include` して使う。
- ライブラリ内部を変更しても、公開インタフェースが同じなら verify コードは原則そのままにする。

## 運用フロー

1. ライブラリを変更する。
2. verify コードに対して、提出用コードを生成（`#include` 展開・コピー）する。
3. 提出先に手動提出する。
4. AC を確認できたら、手動で verify 済みとしてマークする。

## Schieber-Vishkin LCA

- 問題: https://judge.yosupo.jp/problem/lca
- コード: `verify/tree/schieber_vishkin_lca/library_checker_lca.test.cpp`
