# cpp-lib

[![pages](https://img.shields.io/badge/pages-GitHub%20Pages-blue)](https://kkt89.github.io/cpp-lib/)

## リファレンス生成方法

[Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) を使います。

### クイックスタート

```shell
$ uv sync
$ uv run mkdocs serve
```

### 開発用スクリプト

提出用コードの生成・検証状況の管理は [`scripts/README.md`](scripts/README.md) を参照してください。

## ライブラリ使用方法

### CMakeLists を使用する場合

`cpp-lib` を利用側プロジェクトの直下に配置します。

```cmake
add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/cpp-lib/include"
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpplib)
```

## Verify

ジャッジへの提出は手動です。ドキュメント生成時に、登録済みコードと依存ライブラリの変更を検出します。

### テストコードの追加

提出コードと問題情報を登録します。

```shell
uv run scripts/verify.py add main.cpp \
  --url https://judge.yosupo.jp/problem/lca \
  --title "Lowest Common Ancestor"
```

### 検証

ライブラリ変更後、ジャッジで再度 AC を確認したら次のスクリプトを実行します。

```shell
uv run scripts/verify.py mark --all
```
