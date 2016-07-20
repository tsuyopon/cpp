
# 静的リンクされたライブラリの作成と静的リンクされたバイナリの生成を行います

# ポイント
- 共有ライブラリ生成時に-sharedオプションを指定する
- -Wl,-soname,libxxxx.so.0といったように指定する
- バイナリ生成時に-staticを付与してstaticライブラリを指定すると静的リンクされたバイナリを生成できます
- (共有ライブラリだけではないけど)コンストラクタとデストラクタの仕組みを追加

# 実行

executeターゲットを用意しています(今回の場合にはコマンド実行時にLD_LIBRARY_PATHの指定も必要だったので)
```
$ make
rm -f *.o libhello.so* sample
gcc -fPIC -Wall -g -c libhello.c
gcc -g -shared -Wl,-soname,libhello.so.0 -o libhello.so.0.0 libhello.o -lc
/sbin/ldconfig -n .
ln -sf libhello.so.0 libhello.so
gcc -Wall -g -c sample.c -o sample.o
gcc -g -o sample sample.o -L. -lhello
#########################################################
###### use "make execute" target to execute sample library #####
#########################################################
```

今回は共有ライブラリなのでLD_LIBRARY_PATHを設定して実行するのでmake executeを利用します。
今回のサンプルではコンストラクタとデストラクタも動作するように追加しています(共有ライブラリだけの仕組みではありませんが)
```
$ make execute
LD_LIBRARY_PATH="." ./sample
constructor
Hello, library world.
destructor
```

soファイルの関係を確認しておく
```
$ ls -alt libhello.so* 
lrwxrwxrwx 1 tsuyoshi tsuyoshi   13 Jul 20 09:16 libhello.so -> libhello.so.0
lrwxrwxrwx 1 tsuyoshi tsuyoshi   15 Jul 20 09:16 libhello.so.0 -> libhello.so.0.0
-rwxrwxr-x 1 tsuyoshi tsuyoshi 7326 Jul 20 09:16 libhello.so.0.0
```

# 参考
- https://linuxjf.osdn.jp/JFdocs/Program-Library-HOWTO/more-examples.html
