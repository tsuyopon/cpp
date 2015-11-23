backtrace機能とaddr2lineコマンドを使ってデバッグする
====
linuxのlibcには「backtrace(3)」という関数があり、その時点のバックトレースを取得できる。 
これを使ってデバッグをしてみる。

# 概要・設定

addr2line_test.ccのプログラムをgcc -rdynamicでコンパイルして実行すると次のようなバックトレースが表示されます。i386 上では backtrace_symbols_fd() は .dynsym セクション内の情報を利用する (内部的に dladdr を使っている) ため -rdynamic が必要です。 

rdynamicオプションを付与してビルドして実行するとバックトレースを出力してくれます。
static属性が付与されて関数の場合にはシンボルは公開されないので表示されません。
```
$  gcc -rdynamic addr2line_test.c -o prog
$ ./prog  3
backtrace() returned 8 addresses
./prog(myfunc3+0x1f) [0x400a2b]
./prog() [0x400ac0]
./prog(myfunc+0x25) [0x400ae7]
./prog(myfunc+0x1e) [0x400ae0]
./prog(myfunc+0x1e) [0x400ae0]
./prog(main+0x59) [0x400b42]
/lib64/libc.so.6(__libc_start_main+0xf5) [0x3d54621735]
./prog() [0x400929]
```

参考までにrdynamicオプションを付与しない場合には特に関数名は付与されないことがわかります。
```
$  gcc addr2line_test.c -o prog
$ ./prog 3
backtrace() returned 8 addresses
./prog() [0x40078b]
./prog() [0x400820]
./prog() [0x400847]
./prog() [0x400840]
./prog() [0x400840]
./prog() [0x4008a2]
/lib64/libc.so.6(__libc_start_main+0xf5) [0x3d54621735]
./prog() [0x400689]
```

rdynamicを付与したコマンドで表示されたポインタを指定します。
```
$ addr2line -e prog -f 0x400a2b 0x400ae7 0x400ae0 0x400b42     // C++の場合には-Cを指定すると関数名を見やすくします
myfunc3
??:0
myfunc
??:0
myfunc
??:0
main
??:0
```

addr2lineコマンドを簡単に説明します
- e 実行ファイルの位置を指定、デフォルトはa.out
- f 関数名を表示する
- C C++のシンボル名を見やすくする
- s ファイル名のみを表示する(付与しないと絶対パスを表示する)


"??:0"の部分を表示するためには-gオプションを付与してビルドしてシンボルを付加する必要があります。
```
$ gcc -rdynamic addr2line_test.c -o prog -g
$ ./prog 3
backtrace() returned 8 addresses
./prog(myfunc3+0x1f) [0x400a2b]
./prog() [0x400ac0]
./prog(myfunc+0x25) [0x400ae7]
./prog(myfunc+0x1e) [0x400ae0]
./prog(myfunc+0x1e) [0x400ae0]
./prog(main+0x59) [0x400b42]
/lib64/libc.so.6(__libc_start_main+0xf5) [0x3d54621735]
./prog() [0x400929]
$ addr2line -e prog -f 0x400a2b 0x400ae7 0x400ae0 0x400b42
myfunc3
/home/tsuyoshi/git/cpp/hoge/addr2line_test.c:15
myfunc
/home/tsuyoshi/git/cpp/hoge/addr2line_test.c:47
myfunc
/home/tsuyoshi/git/cpp/hoge/addr2line_test.c:44
main
/home/tsuyoshi/git/cpp/hoge/addr2line_test.c:58
```

つまり、backtrace機能とaddr2line機能を使うとどこで問題が発生がしているのかを特定することができます。


