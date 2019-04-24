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


参考までにLD_DEBUG=libsを指定して実行した結果も以下に記載しておく。
```
$ gmake execute
LD_DEBUG=libs LD_LIBRARY_PATH="." ./sample
     31650:	find library=liblibrary1.so.1 [0]; searching
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/liblibrary1.so.1
     31650:	  trying file=./tls/liblibrary1.so.1
     31650:	  trying file=./x86_64/liblibrary1.so.1
     31650:	  trying file=./liblibrary1.so.1
     31650:	
     31650:	find library=liblibrary2.so.1 [0]; searching
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/liblibrary2.so.1
     31650:	  trying file=./tls/liblibrary2.so.1
     31650:	  trying file=./x86_64/liblibrary2.so.1
     31650:	  trying file=./liblibrary2.so.1
     31650:	
     31650:	find library=libc.so.6 [0]; searching
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/libc.so.6
     31650:	  trying file=./tls/libc.so.6
     31650:	  trying file=./x86_64/libc.so.6
     31650:	  trying file=./libc.so.6
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/libc.so.6
     31650:	  trying file=./tls/libc.so.6
     31650:	  trying file=./x86_64/libc.so.6
     31650:	  trying file=./libc.so.6
     31650:	 search cache=/etc/ld.so.cache
     31650:	  trying file=/lib64/libc.so.6
     31650:	
     31650:	find library=libhello.so.1 [0]; searching
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/libhello.so.1
     31650:	  trying file=./tls/libhello.so.1
     31650:	  trying file=./x86_64/libhello.so.1
     31650:	  trying file=./libhello.so.1
     31650:	
     31650:	find library=libhello.so.2 [0]; searching
     31650:	 search path=./tls/x86_64:./tls:./x86_64:.		(RPATH from file ./sample)
     31650:	  trying file=./tls/x86_64/libhello.so.2
     31650:	  trying file=./tls/libhello.so.2
     31650:	  trying file=./x86_64/libhello.so.2
     31650:	  trying file=./libhello.so.2
     31650:	
     31650:	
     31650:	calling init: /lib64/libc.so.6
     31650:	
     31650:	
     31650:	calling init: ./libhello.so.2
     31650:	
liblibrary1 constructor
     31650:	
     31650:	calling init: ./libhello.so.1
     31650:	
liblibrary1 constructor
     31650:	
     31650:	calling init: ./liblibrary2.so.1
     31650:	
liblibrary1 constructor
     31650:	
     31650:	calling init: ./liblibrary1.so.1
     31650:	
liblibrary1 constructor
     31650:	
     31650:	initialize program: ./sample
     31650:	
     31650:	
     31650:	transferring control: ./sample
     31650:	
liblibrary1
Hello1, world.
liblibrary2
Hello1, world.
     31650:	
     31650:	calling fini: ./sample [0]
     31650:	
     31650:	
     31650:	calling fini: ./liblibrary1.so.1 [0]
     31650:	
liblibrary1 destructor
     31650:	
     31650:	calling fini: ./liblibrary2.so.1 [0]
     31650:	
liblibrary1 destructor
     31650:	
     31650:	calling fini: ./libhello.so.1 [0]
     31650:	
liblibrary1 destructor
     31650:	
     31650:	calling fini: ./libhello.so.2 [0]
     31650:	
```

# まとめ
- 異なるバージョンのshared objectに依存(DT_NEEDED)が存在し、呼び出す関数名称が同じ場合先に読み込んだsoバージョン側が呼ばれる。
- コンストラクタ、デストラクタはライブラリを呼び出した回数だけ呼ばれる。コンストラクタとデストラクタも呼び出す関数名称が同じなので上記の条件と同一であることがわかる。


