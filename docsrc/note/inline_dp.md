# インラインDPについて

`ndp` を毎回作る DP を、配列を使い回して in-place に落とすときの注意点をまとめる。

以下のような遷移を考える。

```cpp
vector<mint> dp(n);
dp[s] = 1;

for (...) {
    vector<mint> ndp(n);

    // 全体遷移
    for (int j = 0; j < n; j++) {
        ndp[j] += dp[j] * c;
    }

    // 個別遷移
    ndp[a] += dp[b];

    swap(dp, ndp);
}
```

全体の `* c` は lazy 倍率 `all` でまとめて持てるが、そのまま `dp` を上書きすると壊れやすい。特に `c = 0` のターンと、古い世代のゴミの扱いに注意が要る。

## 1. 新しい世代の値は必ず 0 から始まる

愚直版では毎ターン

```cpp
vector<mint> ndp(n);
```

としているので、新しい配列は全要素 `0` で始まる。

したがって、使い回し版でも「この世代でまだ触っていない状態」は `0` として扱わないといけない。古い配列に残っている値へ、そのまま加算してはいけない。

特に `c = 0` なら全体遷移で全状態が一度消えるので、

```cpp
ndp[a] += dp[b];
```

は意味として

```cpp
new_dp[a] = old_dp[b];
```

であり、

```cpp
new_dp[a] = old_dp[a] + old_dp[b];
```

ではない。

### NG

```cpp
dp[a] += dp[b];
```

## 2. 全体 update が 0 倍になるなら世代を切る

全体遷移

```cpp
for (int j = 0; j < n; j++) {
    ndp[j] += dp[j] * c;
}
```

は、`c != 0` なら lazy 倍率

```cpp
all *= c;
```

で処理できる。

ただし `c = 0` は別で、このときは `all *= 0` としてはいけない。以後の

```cpp
x / all
```

が壊れるからである。

`c = 0` は「全状態が死んだ」とみなし、世代を進めて空配列に戻す。

```cpp
cur++;
all = 1;
```

## 3. 世代管理するなら、加算時にも世代を見る

例えば

```cpp
vector<int> tm(n, -1);
int cur = 0;
```

として、`tm[i] == cur` のときだけその状態が生きているとする。

読むときだけ世代を見るのでは不十分で、書くときも「この世代で初めて触るなら 0 に戻す」が必要になる。

### NG

```cpp
dp[i] += x;
tm[i] = cur;
```

これだと古い世代のゴミに `x` を足してしまう。

### OK

```cpp
auto add_dp = [&](int i, mint x) {
    if (tm[i] != cur) {
        tm[i] = cur;
        dp[i] = 0;
    }
    dp[i] += x;
};
```

## 4. 遷移元は壊す前に読む

`c = 0` のターンでは、世代を進めた瞬間に旧世代の値は全て読めなくなる。必要な遷移元は、世代を進める前に実値として退避しておく。

### NG

```cpp
cur++;

mint src = get_dp(b); // もう死んでいる
```

### OK

```cpp
mint src = get_dp(b) * all;

cur++;
all = 1;

add_dp(a, src);
```

個別遷移が複数あるなら、世代を切る前に必要な遷移元を先に全部読んでおく。

## 5. lazy 倍率では「保存値」と「実値」を混ぜない

`all` を使うとき、`dp[i]` に入っているのは実値そのものではなく

```text
実値 / all
```

である。

したがって、

- 実値を読むときは `get_dp(i) * all`
- 実値 `x` を足すときは `add_dp(i, x / all)`

が必要になる。

## 6. 最後の集計でも世代を見る

最後に総和を取るときも、生きている状態だけを数える。

### NG

```cpp
for (int i = 0; i < n; i++) {
    ans += dp[i] * all;
}
```

### OK

```cpp
for (int i = 0; i < n; i++) {
    if (tm[i] == cur) {
        ans += dp[i] * all;
    }
}
```

## テンプレ

```cpp
vector<mint> dp(n);
vector<int> tm(n, -1);

int cur = 0;
mint all = 1;

auto get_dp = [&](int i) -> mint {
    if (tm[i] != cur) return 0;
    return dp[i];
};

auto add_dp = [&](int i, mint x) {
    if (tm[i] != cur) {
        tm[i] = cur;
        dp[i] = 0;
    }
    dp[i] += x;
};

auto set_dp = [&](int i, mint x) {
    tm[i] = cur;
    dp[i] = x;
};
```

初期状態を入れるときは `set_dp(s, 1);` のようにすればよい。
