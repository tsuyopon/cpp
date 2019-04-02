# 概要
C言語のプログラムにC++のプログラムをリンクするサンプルです。

ポイントはhello.hの中で__cplusplusが定義された場合に限り「extern "C"」で囲んでいます。


次のコマンドでコンパイルします。
```
$ gmake 
cc    -c -o hello.o hello.c
ar rv libhello.a hello.o
ar: creating libhello.a
a - hello.o
g++     main.cc libhello.a   -o main
```

C++で定義されたprint_hello関数がmanglingされていないことを確認します。　
```
$ nm main | grep -i print
0000000000400608 T print_hello
```
