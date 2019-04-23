# ２つのバージョンがリンクされたバイナリを生成して、どのように呼び出されるのかを実験します。
この場合にどちらのバージョンにも定義されるhello()を呼び出した時にどうなるのかを確認します。
```
$ objdump -x sample | grep -i NEEDED | grep -i libhello
  NEEDED               libhello.so.0
  NEEDED               libhello.so.1
```

# ポイント
- libhello.cとlibhello2.cを用意する 
- -l:libhello.c -l:libhello2.cにより両方をリンクさせることでデュアルバージョンに依存したライブラリを準備する

# 実行

```
$ gmake
$ ls -1 *.so*
libhello.so.0
libhello.so.0.0
libhello.so.1
libhello.so.1.0
```

以上により
```
$  objdump -x sample | grep -i NEEDED | grep -i libhello
  NEEDED               libhello.so.0
  NEEDED               libhello.so.1
```

実行してみる。libhello.so.1で定義されるコンストラクタやデストラクタはconstructor2やdestructor2なのでここでは呼ばれなておらず、libhello.so.0側の方が呼ばれているように思われる。
また、実行されているhelloはlibhello.so.0が呼ばれている。
```
$ LD_LIBRARY_PATH=. ./sample 
constructor
constructor
Hello, library world.
destructor
destructor
```

# まとめ
バイナリに複数のライブラリをリンクさせることが可能である。
コンストラクタが２度呼ばれているが、どちらもlibhello.so.0のものしか呼ばれていない。libhello.so.1で定義されているほうもlibhello.so.0として呼ばれたのだろうか?
しかし、使われるライブラリはおそらく最初にELFのNEEDEDにある方だったりするのだろうか?(この辺は推測なので今後検証が必要)



