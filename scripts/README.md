# scripts/

ドキュメント生成まわりの補助スクリプトです。

## `mkdocs_hooks.py`

- **役割**: MkDocs の `on_pre_build` フックで前処理を実行します。
- **実行内容**:
  - `sync_library_index.py` で `docsrc/library/index.md` を同期
  - `bundle_header.py` で `bundled/` を生成

## `bundle_header.py`

- **役割**: `#include` を展開して 1 ファイル化済みヘッダ（`bundled/`）を生成します。
- **通常運用**: `mkdocs serve/build` 実行時に `mkdocs_hooks.py` から自動実行されます。
- **手動実行**:
  ```shell
  uv run python scripts/bundle_header.py <input.hpp> <output.hpp>
  ```

## `sync_library_index.py`

- **役割**: `mkdocs.yml` の `nav` から `docsrc/library/index.md` を生成・同期します。
- **通常運用**: `mkdocs serve/build` 実行時に `mkdocs_hooks.py` から自動実行されるため、手動実行は不要です。
- **手動チェック**: `uv run python scripts/sync_library_index.py`
- **手動更新**: `uv run python scripts/sync_library_index.py --write`
