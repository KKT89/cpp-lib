[![pages](https://img.shields.io/badge/pages-GitHub%20Pages-blue)](https://kkt89.github.io/cpp-lib/)

## リファレンス生成方法

[Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) を用いて作成しています。

### クイックスタート

```shell
$ uv sync
$ uv run python scripts/sync_library_index.py --write
$ uv run mkdocs serve
```

`mkdocs.yml` の `nav` を変更していない場合は、2行目（`sync_library_index.py --write`）は省略可能です。

### ヘッダ結合（1ファイル化）について

- `mkdocs serve/build` の前に `include/**/*.hpp` から `bundled/` を自動生成します（`scripts/mkdocs_hooks.py`）。
- 各ライブラリページの「Bundled (Copy & Paste)」はこの `bundled/` を参照します。

## ライブラリ使用方法

### CMakeListsを使用する場合

以下のように追記すればOK。

```
add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpp)
```
