# エージェント向け作業手順書

## 基本方針

- 回答・説明は日本語で簡潔かつ丁寧に行う。
- このディレクトリは競技プログラミング用 C++ ライブラリ `cpp-lib` である。
- 既存の構成・文体・整形を優先し、勝手に別方式へ変更しない。
- 次は生成物なので手で編集しない（正典は `.gitignore`）。`bundled/`、`site/`、`docsrc/verify/`（配下すべて）、`docsrc/library/index.md`、`docsrc/note/index.md`。
- 説明文では受動態を避ける。ライブラリは機能を「提供する」側なので、「〜される」より「〜する」「〜を返す」「〜を管理する」のように書く。

## ライブラリ追加時の必須ファイル

通常のライブラリを追加するときは、少なくとも次の 2 ファイルを同時に追加する。

1. 実装ヘッダ
    - `include/<category>/<name>.hpp`
2. ライブラリ説明 Markdown
    - `docsrc/library/<category>/<name>.md`

`<category>` は既存カテゴリに合わせること。また、ファイル名は原則 `snake_case` にすること。Markdown と hpp の相対パスは、拡張子以外一致させる。

例:

```text
include/math/crt.hpp
docsrc/library/math/crt.md
```

### hpp と md を対応させる設計理由

`scripts/mkdocs_hooks.py` の `on_page_markdown` は、Markdown のパス `library/<category>/<name>.md` から `include/<category>/<name>.hpp` を逆算し、その hpp が存在するときだけ `## Code` / `## Bundled` / `## Verify` / `## Sub Libraries` を自動挿入するため。

## サブライブラリの扱い

親ライブラリに従属する小さな alias / 補助ライブラリは、Markdown の先頭に frontmatter を付ける。

```markdown
---
parent: math/static_modint.hpp
---

# Static ModInt (998244353)

`mod = 998244353` 固定の [`static_modint`](static_modint.md) のエイリアスです。
```

- `parent` には `include/` からの相対 hpp パスを書く（例: `math/static_modint.hpp`）。
- 指定した `parent` の hpp が実在しないと、スクリプトは frontmatter を無視して通常ライブラリ扱いにするので注意する。
- `parent` があると、スクリプトはそのページを Library Top の通常一覧から外し、親ページの `## Sub Libraries` に表示する。サブ側ページには代わりに `## Parent Library` を自動付与する。
- verify ページでは、サブライブラリを直接 include していても親ライブラリ側へ集約する。
- スクリプトは Markdown を `docsrc/library/<category>/<name>.md` の 2 階層ちょうどでしか走査しない（`docs_catalog.py` の `len(rel.parts) != 2: continue`）。サブライブラリでも md をこれより深い階層へ置かない。
- 現状の「タグ付け」は `tags:` ではなく、この `parent:` frontmatter で行う（`read_meta` は `key: value` 形式のみ解釈）。
- alias 系のサブライブラリでは、hpp 側も親を include して薄く包む（例: `static_modint_998244353.hpp` は `#include "math/static_modint.hpp"`）。

## hpp の書き方

### 基本形

```cpp
#pragma once
#include <vector>

struct Example {
    // ...
};
```

- 先頭は必ず `#pragma once`。
- ヘッダ内で `#include <bits/stdc++.h>` や `using namespace std;` は使わない。
- 必要な標準ヘッダを明示的に include する。
- 標準ライブラリ名は `std::vector` のように `std::` を付ける。
- ローカル依存は `#include "math/static_modint.hpp"` のように `include/` からの相対パスで書く。
- ヘッダ単体で include できるように、依存を利用者側に押し付けない。

### C++ スタイル

`.clang-format` に従うこと。また、既存ライブラリに合わせ、以下を意識する。

- テンプレート型名は `T`, `S` など短くすることが多い。
- 構造体名は既存に合わせる。
    - 低レイヤのデータ構造は `binary_trie`, `segtree` など `lower_snake_case` が多い。
    - 既存の `UnionFind`, `LowestCommonAncestor` のような `UpperCamelCase` もあるため、近いライブラリに合わせる。
- `{}` は基本的に省略しない。`if` / `else` / `for` / `while` の本体が 1 文でもブロックを書く。
- ただし、単純な早期 return や境界チェックなどの短い `if` は例外として 1 行で書いてよい。
- 計算量・制約・非自明な実装意図はコメントで残す。
- コメントは日本語でよい。
- namespace を閉じるときは clang-format 後の形に合わせる。

```cpp
}  // namespace factorize
```

## Markdown の書き方

### 基本構成

通常のライブラリページは、次の形を基本にする。

````markdown
# Library Title

ライブラリの概要を 1〜2 文で説明します。

## Interface

```cpp
Example ex(n);        // n 要素で初期化
ex.add(x);            // x を追加
T ans = ex.query();   // 答えを取得
```

## Notes

- 必要なら制約や注意点を書く。
````

- 先頭は `# タイトル`。
- タイトルの次に空行を入れ、概要文を書く。
- 基本的に `## Interface` を置き、使い方を短い C++ コードで示す。
- 必要な場合のみ `## Notes` を追加する。
- `## Code`、`## Bundled`、`## Verify`、`## Sub Libraries` は `mkdocs_hooks.py` が自動生成するため手で書かない。
- `docsrc/library/index.md` は自動生成なので手で編集しない。
- 概要文・Notes・Interface のコメントでは受動態を避ける。
    - よい例: `整数の多重集合を管理し、XOR に関するクエリを高速に処理します。`
    - 避ける例: `整数の多重集合が管理され、XOR に関するクエリが処理されます。`
- `mkdocs.yml` は `strict: true`。リンク切れや見出し不整合などの警告でも build が失敗する。相対リンク（例: `[static_modint](static_modint.md)`）は実在するページを指す。
- 数式は `$ ... $` / `$$ ... $$`（arithmatex）、コードは ```` ```cpp ```` フェンスを使う。

### Interface コードブロックのコメント位置

Interface のコードブロックでは、行末コメントの `//` の開始位置を揃える。

- 同じコードブロック内で、コメント前のコード部分が最も長い行を基準にする。
- `//` は「最長のコード部分 + 半角スペース 3 個」の列に置く。
- タブは使わない。
- コメントは短く、利用方法・計算量・前提を書く。

例:

```cpp
Foo foo(n);                // n 要素で初期化
foo.update(i, x);          // i 番目を x に更新, O(log n)
long long v = foo.all();   // 全体の値を取得, O(1)
```

## Verify の追加・更新

verify の追加・登録・検証はユーザー（人間）の作業である。エージェントは `verify/` 配下にファイルを作らない。ライブラリ追加・変更時に verify を用意する必要はなく、hpp と md だけでよい。

## 生成・確認手順

ライブラリ追加後の基本確認は、`cpp-lib` 直下で行う。`strict: true` なので、build がエラーなく通ること自体がリンク・書式・対応関係の検証になる。

```shell
uv run mkdocs build
```

この build でスクリプトは主に以下を（再）生成する。すべて `.gitignore` 対象なので、生成物そのものをコミットしない。

- `bundled/**/*.hpp`、`bundled/verify/**/*.cpp`
- `docsrc/library/index.md`、`docsrc/note/index.md`
- `docsrc/verify/`（index.md と各ページ）
- `site/`

build 時、`scripts/mkdocs_hooks.py` は stale / 未登録の verify を標準エラーへ警告する。これは登録待ちや hash ずれの把握用で、解消（登録・再検証）はユーザーが行う。エージェントは警告を消すために `verify/` を触らない。

## 追加前後チェックリスト（エージェント側）

- [ ] `include/<category>/<name>.hpp` を追加した。
- [ ] `docsrc/library/<category>/<name>.md` を追加した（hpp と拡張子以外一致、2 階層ちょうど）。
- [ ] サブライブラリなら md 先頭に `parent: <実在する parent.hpp>` を付けた。
- [ ] hpp は `#pragma once`、必要 include、`std::` 明示。`bits/stdc++.h` や `using namespace std;` を使っていない。
- [ ] Interface の `//` は「最長コード + 3 スペース」の列で揃え、タブを使っていない。
- [ ] `## Code` / `## Bundled` / `## Verify` / `## Sub Libraries` を md に手書きしていない。
- [ ] `uv run mkdocs build` が `strict` でエラーなく通る（リンク切れ・見出し不整合がない）。
- [ ] 生成物（`bundled/`・`site/`・`docsrc/verify/`・各 `index.md`）を直接コミットしていない。
