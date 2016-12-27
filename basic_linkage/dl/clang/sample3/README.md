# dlopenしたsoの中から、mainと共有ライブラリ双方に同一の関数名が定義されている場合にどちらの関数を呼ぶかを決定する

## 課題
- main.cと共有ライブラリhello.c双方にhoge()という関数が定義されていて、ライブラリから呼び出されるがどちらが呼ばれるのか?

## ポイント
- デフォルトではmain側のライブラリの関数が用意される。
- ライブラリ内部側のhoge()を実行するには、共有ライブラリのビルド時に-Bsymbolicオプションを付与すると良い。
- 今回のMakefileではターゲットで各々のパターンを生成できる

## 実行結果
- mainファイル中のhogeを呼び出す場合
```
$ make main1
gcc -shared hello.c -o hello.so -fPIC
gcc -export-dynamic main.c -o main -ldl
$ ./main 
Library Hello, 200
I'm hoge in main file
201
```

- 共有ライブラリ(hello.c)ファイル中のhogeを呼び出す場合
```
$ make main2
gcc -Wl,-Bsymbolic -shared hello.c -o hello.so -fPIC
gcc -export-dynamic main.c -o main -ldl
$ ./main 
Library Hello, 200
I'm hoge in library
201
```

## 参考
- http://d.hatena.ne.jp/dayflower/20080523/1211531833
