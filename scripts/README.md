# scripts/

## 手動で実行するもの

通常のドキュメント閲覧には `uv run mkdocs serve` だけで十分です。以下は必要な場面で手動実行するスクリプトです。

- `verify.py`
  Verify コードの登録・鮮度確認・検証済みマークを行う CLI です。Verify 運用を回すときに使用します。
- `combine.py`
  提出用の `submit.cpp` を生成し、必要ならクリップボードへコピーします。ライブラリ管理や docs 生成には不要です。

## `verify.py`

新規登録：

```shell
uv run scripts/verify.py add main.cpp \
  --url https://judge.yosupo.jp/problem/lca \
  --title "Lowest Common Ancestor"
```

検証済みとしてマーク：

```shell
uv run scripts/verify.py mark verify/library_checker/lowest_common_ancestor.cpp
uv run scripts/verify.py mark --all
```

## 内部処理

- `mkdocs_hooks.py`
  MkDocs のフック本体です。nav 差し替え、`bundled/` 生成、`docsrc/library/` / `docsrc/verify/` の自動生成を行います。
- `docs_catalog.py`
  Library / Note のスキャン、nav / index 生成、ライブラリページ末尾の管理セクション生成を担当します。
- `verify_docs.py`
  Verify ページ、Verify index、Verify nav の生成を担当します。
- `verify_data.py`
  `verify/status.json` の読み書き、ハッシュ計算、judge URL 解決など Verify 系の共通処理です。
- `bundle_header.py`
  `#include` を展開して `bundled/` の単一ファイルを生成します。
- `project_paths.py`
  `scripts/` 内で共有するパス定義です。
