# 概要
gcovについて

# sample1について
次のコマンドでコンパイルします。gcov用のバイナリを生成して実行する必要があります。
gcov用のバイナリを作るにはgccにオプションとして-fprofile-arcs -ftest-coverage(新しいgccだと-coverageを)を付加します。 
```
$ make sample1
```

実行するとバイナリsample1の他にsample1.gcnoが生成されます。
その後にバイナリを実行した直後にlsしてみるとgcdaという拡張子のファイルが生成されます。
```
$ ./sample1 
5
7
$ ls sample1*
sample1  sample1.c  sample1.gcda  sample1.gcno
```

続いてgcovコマンドでgcdaのファイルを引数として渡して実行すると、今度はgcovという拡張子のファイルが生成されます。
```
$ gcov sample1.gcda 
File 'sample1.c'
Lines executed:75.00% of 8
Creating 'sample1.c.gcov'
$ ls sample1*
sample1  sample1.c  sample1.c.gcov  sample1.gcda  sample1.gcno
```

中を覗いてみる。fooが2度呼ばれていて、barが呼ばれていないということが確認できる。
```
$ cat sample1.c.gcov 
        -:    0:Source:sample1.c
        -:    0:Graph:sample1.gcno
        -:    0:Data:sample1.gcda
        -:    0:Runs:1
        -:    0:Programs:1
        -:    1:#include <stdio.h>
        -:    2:
        2:    3:int foo(int x, int y) {
        2:    4:  return x + y;
        -:    5:}
        -:    6:
    #####:    7:int bar(int x, int y) {
    #####:    8:  return x - y;
        -:    9:}
        -:   10:
        1:   11:int main(void) {
        1:   12:  printf("%d\n", foo(2, 3));
        1:   13:  printf("%d\n", foo(3, 4));
        1:   14:  return 0;
        -:   15:}
```

以上で簡単な説明はおしまい。  

- 参考
  - http://d.hatena.ne.jp/ku-ma-me/20090721/p1


# 参考URL
- 公式ドキュメント(英語)
  - https://gcc.gnu.org/onlinedocs/gcc/Gcov.html
- 公式ドキュメント(日本語)
  - http://www.asahi-net.or.jp/~wg5k-ickw/html/online/gcc-2.95.2/gcc_6.html
