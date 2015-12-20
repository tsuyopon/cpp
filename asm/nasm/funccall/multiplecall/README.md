C言語からアセンブラ関数を呼び出す
====

# ポイント
アセンブラで呼び出す関数に対する引数は複数個指定されるパターン

# 実行
以下を実行すればOK
```
$ gmake clean
$ gmake
```

gdbなどで調査する場合には以下のサンプルコマンド実行を参考にトレースしてみると良い
```
$ gdb ./main
(gdb) b addfunc
(gdb) run
(gdb) disas
(gdb) stepi
(gdb) info r
(gdb) x/20xw $rbp
```
