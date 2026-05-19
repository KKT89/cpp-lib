# scripts/

補助スクリプト群です。

## ファイル一覧

- `mkdocs_hooks.py`
  MkDocs のフック本体です。nav 差し替え、`bundled/` 生成、`docsrc/library/` / `docsrc/verify/` の自動生成を行います。
- `docs_catalog.py`
  Library / Note のスキャン、nav / index 生成、ライブラリページ末尾の管理セクション生成を担当します。
- `verify_docs.py`
  Verify ページ、Verify index、Verify nav の生成を担当します。
- `verify_data.py`
  `verify/status.json` の読み書き、ハッシュ計算、judge URL 解決など Verify 系の共通処理です。
- `verify.py`
  Verify コードの登録・鮮度確認・検証済みマークを行う CLI です。
- `bundle_header.py`
  `#include` を展開して `bundled/` の単一ファイルを生成します。
- `combine.py`
  提出用の `submit.cpp` を生成し、必要ならクリップボードへコピーします。
- `project_paths.py`
  `scripts/` 内で共有するパス定義です。

## Verify CLI

新規登録:

```shell
uv run scripts/verify.py add main.cpp \
  --url https://judge.yosupo.jp/problem/lca \
  --title "Lowest Common Ancestor"
```

検証済みとしてマーク:

```shell
uv run scripts/verify.py mark verify/library_checker/lowest_common_ancestor.cpp
uv run scripts/verify.py mark --all
```
