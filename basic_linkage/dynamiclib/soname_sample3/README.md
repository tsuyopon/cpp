# 概要
1つのプログラムsampleから2つの異なるバージョンのso中の関数を呼び出してそこからsoバージョンが異なるそれぞれのhello()を呼び出すプログラムを作成した。　
```
sample ---------- liblibrary.so.1.0
            |         |
            |         |----------------- libhello.so.1.0   // 内部にhello()が定義
            |
            |
            ----- liblibrary.so.2.0
                      |
                      |----------------- libhello.so.2.0   // 内部にhello()が定義
```

このパターンではsampleは次のようなソースコードになっている。
```
#include "liblibrary1.h"
#include "liblibrary2.h"

int main(void) {
    liblibrary1();   // libhello.so.1.0のhello()を呼び出すことを期待している
    liblibrary2();   // libhello.so.2.0のhello()を呼び出すことを期待している
    return 0;
}
```

実行してみると次のような結果となった。
```
$ gmake execute
LD_LIBRARY_PATH="." ./sample
liblibrary1 constructor
liblibrary1 constructor
liblibrary1 constructor
liblibrary1 constructor
liblibrary1
Hello1, world.
liblibrary2
Hello1, world.
liblibrary1 destructor
liblibrary1 destructor
liblibrary1 destructor
liblibrary1 destructor
```


