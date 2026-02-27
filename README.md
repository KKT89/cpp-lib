# cpp-lib

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

### CMakeLists を使用する場合

```cmake
add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpplib)
```

## Verify (テストコード)

ライブラリの正当性を確認するテストコードを `verify/` で管理しています。
ジャッジへの提出のみ手動で行う半自動運用です。ライブラリやテストコードに変更があると staleness を自動検知し、再検証が必要な箇所を把握できます。

### テストの追加

ジャッジで AC を確認した `.cpp` を登録します。

```shell
uv run scripts/verify_status.py add main.cpp \
  --url https://judge.yosupo.jp/problem/lca \
  --title "Lowest Common Ancestor"
```

### 検証済みとしてマーク

ライブラリ変更後、ジャッジで再度 AC を確認したら実行します。

```shell
uv run scripts/verify_status.py mark --all
```
