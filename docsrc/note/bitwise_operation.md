# ビット演算あれこれ

## 末尾の0個数

c++20以降ならば、[std::countr_zero](https://cpprefjp.github.io/reference/bit/countr_zero.html) を使うのが良い。

## 1が立っているビットを全て知りたい

以下のようなコードが定数倍軽くておススメ。TODO：↑で書き換える。

```c++
while(n) {
  int i = __builtin_ctz(n);
  n ^= 1 << i;
}
```

## __builtin_clz の高速化について

`target("lzcnt")` で速くなるらしい。tzcnt が入ってる命令セットが BMI1 なので、 `target("bmi")`を用いる。

### 参考
- [https://twitter.com/noshi91/status/1645808228067078144](https://twitter.com/noshi91/status/1645808228067078144)
- [x86 Bit manipulation instruction set - Wikipedeia](https://en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set)