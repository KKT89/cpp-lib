[![pages](https://img.shields.io/badge/pages-GitHub%20Pages-blue)](https://kkt89.github.io/cpp-lib/)

## リファレンス生成方法

[Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) を用いて作成しています。

### クイックスタート

```shell
$ uv sync
$ uv run mkdocs serve
```

### 開発用スクリプト

スクリプトに関する説明は [`scripts/README.md`](scripts/README.md) に記載しています。

## ライブラリ使用方法

### CMakeListsを使用する場合

以下のように追記すればOK。

```
add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpp)
```
