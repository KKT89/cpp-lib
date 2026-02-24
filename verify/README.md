# verify 方針

- verify コードは `verify/<category>/<library_key>/<judge>/` に置く。
- verify コードは `<problem>.test.cpp` で命名する。
  - 例: `verify/tree/lowest_common_ancestor/library_checker/lca.test.cpp`
  - 例: `verify/tree/lowest_common_ancestor/atcoder/abc014_d.test.cpp`
- verify ドキュメントは `docsrc/verify/<category>/<library_key>/<judge>/` に置く。
- verify ドキュメントは `<problem>.md` で命名する。
  - 例: `docsrc/verify/tree/lowest_common_ancestor/library_checker/lca.md`
- 1ライブラリに対して複数ジャッジの verify を並べる（1:多）。
- verify コードが複数ライブラリにまたがる場合は primary ライブラリのディレクトリに置き、ドキュメントの Target Library に全て列挙する。
- verify コードの `#include` は include ディレクトリ相対パスで記述する。
  - 例: `#include "tree/lowest_common_ancestor.hpp"`
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
- コード: `verify/tree/lowest_common_ancestor/library_checker/lca.test.cpp`
