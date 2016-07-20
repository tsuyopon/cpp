# weakシンボルを利用してdlsymなどで関数が実装されないパターンを考慮する

## 課題
- 呼び出す関数実装が存在する場合と存在しない場合で処理を分岐したい場合

## ポイント
- __atribute__((weak))を使って弱い参照
 - nmでシンボルを確認するとw記号が確認できます。

## 実行結果
- SETHOGE定義変数がセットされるとhoge()が実装されたことになります。
```
$ make main1
rm -f main hello.so
gcc -DSETHOGE -shared hello.c -o hello.so -fPIC
gcc -export-dynamic main.c -o main -ldl
[tsuyoshi@localhost sample5]$ ./main 
Library Hello, 200
I'm hoge in library
201
```

ついでにシンボル記号も確認します
```
$ nm hello.so | grep -i hoge
0000000000000710 W hoge
```

続いて、SETHOGEをセットしない場合にはhoge()が実装されていないことになるので

```
$ make main2
rm -f main hello.so
gcc -shared hello.c -o hello.so -fPIC
gcc -export-dynamic main.c -o main -ldl
$ ./main 
Library Hello, 200
not implement hoge()
201
```

ついでにシンボル記号も確認します
```
$ nm hello.so | grep -i hoge
                 w hoge
```

## 参考
- http://blog.karky7.com/2014/04/weak.html
