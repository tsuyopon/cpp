# あとで呼ばれた共有ライブラリの中からそれ以前に呼ばれた共有ライブラリ中の関数を呼び出す

## ポイント
- 最初のdlopenしたsoファイル中のシンボルを、その後dlopenしたものから読み込む場合にはフラグ設定が必要になるということ
 - hello2.soからhello.soの関数を実行している
- dlopen時のフラグでRTLD\_GLOBALを指定することによって、その後dlopenされた中に含まれる関数からも呼び出す事ができる。

## 実行
main.ccでRTLDGLOBALを定義変数として指定するかどうかでdlopenのオプションを切り替えている。

RTLD\_GLOBALを指定しない場合には、hello2.soからhello.soの関数(helloecho)を呼び出すとundefined symbolとなる
```
$ make main1
gcc -shared hello.c  -o hello.so -fPIC
gcc -shared hello2.c -o hello2.so -fPIC
gcc -export-dynamic main.c -o main -ldl
$ ./main 
Hello, 200
201
./main: symbol lookup error: ./hello2.so: undefined symbol: helloecho
```

RTLD\_GLOBALを指定した場合には、hello2.soからhello.soの関数(helloecho)を呼び出してもシンボルが参照できる
```
$ make main2
gcc -shared hello.c  -o hello.so -fPIC
gcc -shared hello2.c -o hello2.so -fPIC
gcc -DRTLDGLOBAL -export-dynamic main.c -o main -ldl
$ ./main 
Hello, 200
201
this is hello199
```
