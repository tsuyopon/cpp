
# 静的リンクされたライブラリの作成と静的リンクされたバイナリの生成を行います

# ポイント
- arコマンドでオブジェクトを引数に指定するとstaticライブラリを作成できます。
- バイナリ生成時に-staticを付与してstaticライブラリを指定すると静的リンクされたバイナリを生成できます

# 実行
```
$ make all
rm -f *.o *.a sample
gcc -Wall -g -c -o libhello-static.o libhello.c
ar rcs libhello-static.a libhello-static.o
gcc -Wall -g -c sample.c -o sample.o
gcc -static -g -o sample sample.o -L. -lhello-static
$ ./sample 
Hello, library world.
```

Staticライブラリであることを確認します。
```
$ ldd libhello-static.a 
ldd: warning: you do not have execution permission for `./libhello-static.a'
	not a dynamic executable
```

一応バイナリファイルを確認してみます。
```
$ ldd sample
	not a dynamic executable
```

# 注意点
コンパイル時にlcが見つからないといったエラーが表示されたら
```
$ make
rm -f *.o *.a sample
gcc -Wall -g -c -o libhello-static.o libhello.c
ar rcs libhello-static.a libhello-static.o
gcc -Wall -g -c sample.c -o sample.o
gcc -static -g -o sample sample.o -L. -lhello-static
/usr/bin/ld: cannot find -lc
collect2: error: ld returned 1 exit status
make: *** [all] Error 1
```

以下のパッケージをインストールしてください。
```
$ yum install glibc-static
```

# 参考
- https://linuxjf.osdn.jp/JFdocs/Program-Library-HOWTO/more-examples.html
