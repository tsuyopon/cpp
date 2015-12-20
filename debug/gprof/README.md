gprofによるプロファイリング
====

# 概要・設定
gprofを使った非常に単純な使い方を示します。

コンパイルの際に-pgオプションを指定して、一度実行するとgmon.outというファイルが生成される。
```
$ g++ -pg -o gproftest gproftest.cc
$ ./gproftest
```

これをgprofコマンドに指定すればよい。
```
$ gprof ./gproftest gmon.out
```

Makefileとしては以下のターゲットを指定できます
```
$ gmake compile
$ gmake execute
```

