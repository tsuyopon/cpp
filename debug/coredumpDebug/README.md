CoreDumpによるデバッグを行う
====

# 概要・設定

ulimitコマンドを使ってcoreを吐かせる設定にしましょう。
ulimit -aコマンドでセグフォになった際にcoreを吐かせる設定かどうかを確認して、必要ならばcoreを吐かせましょう。
```
$ ulimit -a | grep -i core 
core file size          (blocks, -c) 0           // これはcoreを出力しない設定
$ ulimit -c unlimited
$ ulimit -a | grep -i core 
core file size          (blocks, -c) unlimited
```

特定のデーモンプロセスなどでcoreファイルを出力する設定になっているかは以下で確認できます。
出力内容のMax core file sizeを確認する。0になっていればcoreファイルは出力されない
```
# cat /proc/%%プロセスID%%/limits
```

もし、稼働中のプロセスにcoreを吐かせる場合(デッドロックなど)にはSIGSEGV(Segmentation Violation)シグナルを送付します。
```
# kill -SIGSEGV %%プロセスID%%
```

今回はzeroDiv.cがあってこれを実行するとセグフォがおき、その際にcoreが生成されるのでこれをgdbでアクセスしてみましょう。
コンパイル時にエラーが出ますがここでは実験のため無視してください。
```
$ gcc zeroDiv.c -o zeroDiv
zeroDiv.c: In function 'foo':
zeroDiv.c:3:17: warning: division by zero [-Wdiv-by-zero]
$ ./zeroDiv 
Floating point exception (core dumped)
$ ls core*
core.3061
```
coreとプロセス番号のファイル名が組み合わさったcoreファイルが生成されました。
gdbでアタッチするには以下のようにします。
```
$ gdb ./a.out core.3061 
```

ここから先はgdbの範疇なので詳細は説明しません。

# 参考URL
- http://qiita.com/suzutsuki0220/items/aa84d7e2e8f37e867f3d
