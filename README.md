↓整備中・・・
取り合えず今まで使ってきたライブラリの整理をしたいなぁ～というステータスです。

[![pages](https://img.shields.io/badge/pages-GitHub%20Pages-blue)](https://kkt89.github.io/cpp-lib/)

## リファレンス生成方法

[Material for MkDocs](https://squidfunk.github.io/mkdocs-material/) を用いて作成しています。

### セットアップ

```shell
$ uv venv .venv
$ source .venv/bin/activate
$ uv pip install -r requirements.txt
```

以下のコマンドが正しく実行出来ればOKです。

```shell
$ mkdocs serve
```

## ライブラリ使用方法

### CMakeLists を使用する場合

以下のように追記すればOK。

```
add_library(cpplib INTERFACE)
target_include_directories(cpplib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpp)
```