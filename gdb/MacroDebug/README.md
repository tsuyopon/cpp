# 概要
defineされたマクロ情報は通常gdbではデバッグすることができませんがg3オプション付きでコンパイルするとデバッグできるようになります。

# 詳細

gオプションではマクロ情報は入りませんが、g3オプションでマクロ情報も含まれます。また、O0は最適化されないように念のために付与しています。
```
$ gcc -g3 -O0 test.c 
```

a.outが生成されたらgdbを実行してみます。mainまで到達したらHOGEやNUMBERを確認できます
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/a.out...done.
(gdb) b main
Breakpoint 1 at 0x400581: file test3.c, line 6.
(gdb) run
Starting program: /home/tsuyoshi/./a.out 

Breakpoint 1, main () at test3.c:6
6		printf("Hello World\n"); 
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) list
1	#include<stdio.h>
2	#define HOGE "fuga"
3	#define NUMBER 100
4	
5	int main(){ 
6		printf("Hello World\n"); 
7		printf("%s\n", HOGE);
8		printf("%d\n", NUMBER);
9	}
(gdb) p HOGE
$1 = "fuga"
(gdb) p NUMBER
$2 = 100
```

HOGEやNUMBERの値が表示されていることを確認できます。
