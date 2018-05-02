# 概要
関数ポインタに関して次の２つについてgdbを使って確認します。
- 関数ポインタに定義された関数を知る方法について
- コールバックがセットされるのを検知する方法について

# 詳細
main関数の中で関数ポインタとしての変数を定義しています。
```
FUNCPTR tFuncPtr;
```

あとは単順にmain関数のブレークポイントに引っかかり次第、"watch tFuncPtr"を実行するだけです。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/git/cpp/gdb/FunctionPointerCallbackCheck/a.out...done.
(gdb) b main
Breakpoint 1 at 0x40055b: file test.c, line 22.
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/gdb/FunctionPointerCallbackCheck/./a.out 

Breakpoint 1, main () at test.c:22
22	    a=8;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) p tFuncPtr       // ここでは特に何も設定されていない
$1 = (FUNCPTR) 0x7fffffffe440
(gdb) watch tFuncPtr   // watchすると関数ポインタ変更時にわかる
Hardware watchpoint 2: tFuncPtr
(gdb) c
Continuing.
Hardware watchpoint 2: tFuncPtr

Old value = (FUNCPTR) 0x7fffffffe440
New value = (FUNCPTR) 0x40052d <multiple>
main () at test.c:26
26	    result=(tFuncPtr)(a,b);
(gdb) p tFuncPtr       // multipleが関数ポインタに設定されていることがわかる
$2 = (FUNCPTR) 0x40052d <multiple>
(gdb) c
Continuing.
Answer is 32
Hardware watchpoint 2: tFuncPtr

Old value = (FUNCPTR) 0x40052d <multiple>
New value = (FUNCPTR) 0x400540 <divide>
main () at test.c:30
30	    result=(tFuncPtr)(a,b);
(gdb) p tFuncPtr       // divideが関数ポインタに設定されていることがわかる
$3 = (FUNCPTR) 0x400540 <divide>
(gdb) list
18	    int a,b;
19	    int result;
20	    FUNCPTR tFuncPtr;
21	
22	    a=8;
23	    b=4;
24	
25	    tFuncPtr=&multiple;
26	    result=(tFuncPtr)(a,b);
27	    printf("Answer is %d\n",result);
28	
29	    tFuncPtr=&divide;
30	    result=(tFuncPtr)(a,b);
31	    printf("Answer is %d\n",result);
32	}
(gdb) c
Continuing.
Answer is 2
```
