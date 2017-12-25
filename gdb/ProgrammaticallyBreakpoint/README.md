# 概要
gdbでブレークポイントを貼らずとも自動的に指定した箇所で停止させる方法について

# 詳細
### test1.c
次のコードを追加することによって停止させることができます。
```
asm("int $3");
or
__asm__("int $3");
```

gdbの実行例は以下
```
$ gcc -g test1.c
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/a.out...done.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/./a.out 

Program received signal SIGTRAP, Trace/breakpoint trap.
main (argc=1, argv=0x7fffffffe3f8) at test1.c:5
5	    int a = 3;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) where
#0  main (argc=1, argv=0x7fffffffe3f8) at test1.c:5
(gdb) list
1	
2	void main(int argc, char** argv)
3	{
4	    asm("int $3");    // 「__asm__("int $3");」としても動作する
5	    int a = 3;
6	    a++;  //  In gdb> print a;  expect result to be 3
7	}
(gdb) c
Continuing.
[Inferior 1 (process 12667) exited with code 0355]
```

### test2.c
C言語では次のsignalによっても停止させることができます。
```
#include <signal.h>
raise(SIGINT);
```

gdbの実行例は以下
```
$ gcc -g test2.c
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/a.out...done.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/./a.out 
before

Program received signal SIGINT, Interrupt.
0x00007ffff7a4d1f7 in raise () from /lib64/libc.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) where
#0  0x00007ffff7a4d1f7 in raise () from /lib64/libc.so.6
#1  0x00000000004005a0 in main (argc=1, argv=0x7fffffffe3f8) at test2.c:7
(gdb) list
1	#include <stdio.h>
2	#include <signal.h>
3	
4	void main(int argc, char** argv)
5	{
6	    printf("before\n");
7	    raise(SIGINT);
8	    printf("after\n");
9	}
(gdb) c
Continuing.
after
[Inferior 1 (process 12597) exited with code 06]
```

### test3.cc (C++)
C++の場合には、次の箇所で停止させることができます。
```
#include <csignal>

// Generate an interrupt
std::raise(SIGINT);
```

gdbの実行例は以下
```
$ g++ -g test3.cc
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/a.out...done.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/ProgrammaticallyBreakpoint/./a.out 
before

Program received signal SIGINT, Interrupt.
0x00007ffff722d1f7 in raise () from /lib64/libc.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) where
#0  0x00007ffff722d1f7 in raise () from /lib64/libc.so.6
#1  0x0000000000400660 in main (argc=1, argv=0x7fffffffe3f8) at test3.cc:7
(gdb) list
1	#include <stdio.h>
2	#include <csignal>
3	
4	int main(int argc, char** argv)
5	{
6	    printf("before\n");
7	    std::raise(SIGINT);
8	    printf("after\n");
9	}
(gdb) c
Continuing.
after
[Inferior 1 (process 12632) exited normally]
```

# 参考URL
- https://stackoverflow.com/questions/4326414/set-breakpoint-in-c-or-c-code-programmatically-for-gdb-on-linux
