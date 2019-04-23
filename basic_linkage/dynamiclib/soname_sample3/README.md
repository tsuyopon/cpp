# 概要
1つのプログラムsampleから2つの異なる共有ライブラリ中の関数を呼び出す。そのsoからはそれぞれ別バージョンのsoのhello()を呼び出すプログラムを作成した。
```
sample ---------- liblibrary1.so.1.0
            |         |
            |         |----------------- libhello.so.1.0   // 内部にhello()が定義
            |
            |
            ----- liblibrary2.so.1.0
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

# まとめ
- 異なるバージョンのshared objectに依存(DT_NEEDED)が存在し、呼び出す関数名称が同じ場合先に読み込んだsoバージョン側が呼ばれる。
- コンストラクタ、デストラクタはライブラリを呼び出した回数だけ呼ばれる。コンストラクタとデストラクタも呼び出す関数名称が同じなので上記の条件と同一であることがわかる。


