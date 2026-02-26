# scripts/

ドキュメント生成まわりの補助スクリプトです。

## `mkdocs_hooks.py`

- **役割**: MkDocs の `on_pre_build` フックで前処理を実行します。
- **実行内容**:
  - `sync_library_index.py` で `docsrc/library/index.md` を同期
  - `bundle_header.py` で `bundled/` を生成
  - `verify/status.json` から `docsrc/verify/index.md` を自動生成

## `bundle_header.py`

- **役割**: `#include` を展開して 1 ファイル化済みヘッダ（`bundled/`）を生成します。
- **通常運用**: `mkdocs serve/build` 実行時に `mkdocs_hooks.py` から自動実行されます。
- **手動実行**:
  ```shell
  uv run scripts/bundle_header.py <input.hpp> <output.hpp>
  ```

## `sync_library_index.py`

- **役割**: `mkdocs.yml` の `nav` から `docsrc/library/index.md` を生成・同期します。
- **通常運用**: `mkdocs serve/build` 実行時に `mkdocs_hooks.py` から自動実行されるため、手動実行は不要です。
- **手動チェック**: `uv run scripts/sync_library_index.py`
- **手動更新**: `uv run scripts/sync_library_index.py --write`

## `combine.py`

- **役割**: `main.cpp` の `#include` を展開し、提出用の単一ファイル (`submit.cpp`) を生成します。生成後、クリップボードへ自動コピーします。
- **セットアップ**: プロジェクトルートにシェルラッパーを作成します。
  ```shell
  cat <<'EOF' > combine
  #!/bin/sh
  exec python3 "$(dirname "$0")/cpp-lib/scripts/combine.py" "$@"
  EOF
  chmod +x combine
  ```
- **実行**:
  ```shell
  ./combine                          # main.cpp -> submit.cpp (クリップボードにコピー)
  ./combine sol.cpp -o out.cpp       # 入出力を指定
  ./combine --no-clipboard           # クリップボードへのコピーをスキップ
  ./combine --include-dir path/to/   # インクルードディレクトリを追加
  ```

**オプション**

| オプション | 説明 |
|------------|------|
| `input` | 入力ファイル（省略時: `main.cpp`） |
| `-o, --output` | 出力ファイル（省略時: `submit.cpp`） |
| `--no-clipboard` | クリップボードへのコピーをスキップ |
| `--include-dir` | インクルードディレクトリを追加（複数指定可） |

## `verify_status.py`

- **役割**: ライブラリ変更による verify コードの staleness を検出します。
- **仕組み**: verify `.cpp` をバンドル → SHA-256 ハッシュ → `verify/status.json` の記録値と比較。
- **新規登録**:
  ```shell
  uv run scripts/verify_status.py add main.cpp --url https://judge.yosupo.jp/problem/lca --title "Lowest Common Ancestor (Library Checker)"
  ```
- **チェック**:
  ```shell
  uv run scripts/verify_status.py check
  ```
- **検証済みとしてマーク**（ジャッジに手動提出して AC 確認後）:
  ```shell
  uv run scripts/verify_status.py mark verify/library_checker/lowest_common_ancestor.cpp
  uv run scripts/verify_status.py mark --all
  ```
