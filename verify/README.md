# verify 方針

- verify コードは `verify/<category>/` に置く。
- verify コードは `(<library_key>).(<judge>)_(<problem_key>).test.cpp` で命名する。
  - 例: `lowest_common_ancestor.library_checker_lca.test.cpp`, `lowest_common_ancestor.atc_abc014_d.test.cpp`
- verify ドキュメントは `docsrc/verify/<category>/` に置く。
- verify ドキュメントは `(<library_key>).(<judge>)_(<problem_key>).md` で命名する。
  - 例: `lowest_common_ancestor.library_checker_lca.md`, `lowest_common_ancestor.atc_abc014_d.md`
- 1ライブラリに対して複数ジャッジの verify を並べる（1:多）。
- verify コードは `include/...` のライブラリを `#include` して使う。
- ライブラリ内部を変更しても、公開インタフェースが同じなら verify コードは原則そのままにする。

## ドキュメント導線ルール

- 中間の「ライブラリ単位 verify ページ」は作らない。
- 導線は `Library ページ -> 各 verify 問題ページ` に統一する。
- `docsrc/verify/index.md` と `mkdocs.yml` の Verify ナビは、verify 問題ページを直接列挙する。

## 運用フロー

1. ライブラリを変更する。
2. verify コードに対して、提出用コードを生成（`#include` 展開・コピー）する。
3. 提出先に手動提出する。
4. AC を確認できたら、手動で verify 済みとしてマークする。

## Lowest Common Ancestor

- 問題: https://judge.yosupo.jp/problem/lca
- コード: `verify/tree/lowest_common_ancestor.library_checker_lca.test.cpp`
