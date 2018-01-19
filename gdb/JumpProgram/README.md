# 概要
特定の分岐を省略してジャンプする方法について

# 詳細
if分岐が複雑でいちいちsetなどを行って面倒な場合などは、jumpコマンドを利用することによってレジスタ(ERP)を書き換えられるので処理を飛ばす事ができます。
jumpの後の引数には行番号を指定できます。ファイルが分割されている場合などは、特定の関数などにブレークポイントを貼ることでそのファイルの行番号を指定します。
```
$ gcc -g test.c
$ gdb ./a.out 
....
(gdb) b main
Breakpoint 1 at 0x400531: file test.c, line 9.
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/gdb/JumpProgram/./a.out 

Breakpoint 1, main () at test.c:9
9	  if( test1 == 1 || test2 == 0 || test3 == 0){
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) list
1	#include<stdio.h>
2	
3	int main()
4	{
5	
6	  static int test1 = 1;
7	  static int test2 = 0;
8	  static int test3 = 0;
9	  if( test1 == 1 || test2 == 0 || test3 == 0){
10	    printf("pattern 1\n");
11	  } else {
12	    printf("pattern 2\n");
13	  }
14	  printf("pattern 3\n");
15	}
16	
(gdb) jump 12
Continuing at 0x40055c.
pattern 2
pattern 3
[Inferior 1 (process 11404) exited with code 012]
```
