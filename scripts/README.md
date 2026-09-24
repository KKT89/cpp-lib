# scripts/

## 手動で実行するもの

ドキュメントの閲覧には `uv run mkdocs serve` を使います。

- `verify.py`
  Verify コードを登録し、AC 後に検証状況を更新します。
- `combine.py`
  提出用の `submit.cpp` を生成し、必要ならクリップボードへコピーします。展開したライブラリ内の標準 `#include` はデフォルトで省略し、`--keep-system-includes` を指定すると残します。

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
  nav の更新、bundle・index・Verify ページの生成を行います。ライブラリ単体の bundle では標準 `#include` を残します。
- `_internal/docs_catalog.py`
  Library / Note のスキャン、nav / index 生成、ライブラリページ末尾の管理セクション生成を担当します。
- `_internal/verify_docs.py`
  Verify ページ、Verify index、Verify nav の生成を担当します。
- `_internal/verify_data.py`
  `verify/status.json` の読み書き、ハッシュ計算、judge URL 解決など Verify 系の共通処理です。
- `bundle_header.py`
  ローカル `#include` を展開して単一ファイルを生成します。エントリファイルの標準 `#include` は常に残し、展開先のものは `--keep-system-includes` 指定時に残します。
- `_internal/docs_common.py`
  タイトル読取や `write_if_changed` など、docs 系の小さい共通処理です。
- `_internal/project_paths.py`
  `scripts/` 内で共有するパス定義です。
