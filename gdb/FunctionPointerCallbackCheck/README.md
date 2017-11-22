# 概要
関数ポインタのコールバックがセットされるのを検知する方法について

# 詳細
main関数の中で関数ポインタとしての変数を定義しています。
```
FUNCPTR tFuncPtr;
```

あとは単順にmain関数のブレークポイントに引っかかり次第、"watch tFuncPtr"を実行するだけです。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/FunctionPointerCallbackCheck/a.out...done.
(gdb) b main
Breakpoint 1 at 0x40055b: file test.c, line 21.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/FunctionPointerCallbackCheck/./a.out 

Breakpoint 1, main () at test.c:21
21	    a=8;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) watch tFuncPtr
Hardware watchpoint 2: tFuncPtr
(gdb) c
Continuing.
Hardware watchpoint 2: tFuncPtr

Old value = (FUNCPTR) 0x7fffffffe3e0
New value = (FUNCPTR) 0x40052d <multiple>
main () at test.c:25
25	    result=(tFuncPtr)(a,b);
(gdb) c
Continuing.
Answer is 32
Hardware watchpoint 2: tFuncPtr

Old value = (FUNCPTR) 0x40052d <multiple>
New value = (FUNCPTR) 0x400540 <divide>
main () at test.c:29
29	    result=(tFuncPtr)(a,b);
(gdb) list
24	    tFuncPtr=&multiple;
25	    result=(tFuncPtr)(a,b);
26	    printf("Answer is %d\n",result);
27	
28	    tFuncPtr=&divide;
29	    result=(tFuncPtr)(a,b);
30	    printf("Answer is %d\n",result);
31	}
```
