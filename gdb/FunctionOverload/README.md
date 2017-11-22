# 概要
関数のオーバーロード時に特定のブレークポイントを指定する方法について

# 詳細

"b abs(int)"などのようにして型なども指定することでオーバーロードで複数の同じ関数名があったとしても特定の関数に絞ることができるようになります。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/define/overload/a.out...done.
(gdb) b abs(int)
Breakpoint 1 at 0x4005f4: file test.cc, line 6.
(gdb) b abs(int, int)
Breakpoint 2 at 0x40060b: file test.cc, line 11.
(gdb) b abs(long)
Breakpoint 3 at 0x400618: file test.cc, line 16.
(gdb) b abs(double)
Breakpoint 4 at 0x400633: file test.cc, line 21.
(gdb) b abs(float)
Function "abs(float)" not defined.
Make breakpoint pending on future shared library load? (y or [n]) n
(gdb) info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004005f4 in abs(int) at test.cc:6
2       breakpoint     keep y   0x000000000040060b in abs(int, int) at test.cc:11
3       breakpoint     keep y   0x0000000000400618 in abs(long) at test.cc:16
4       breakpoint     keep y   0x0000000000400633 in abs(double) at test.cc:21
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/define/overload/./a.out 

Breakpoint 1, abs (x=-8) at test.cc:6
6	  return( (x < 0) ? -x : x );
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) c
Continuing.
8 

Breakpoint 2, abs (x=1, y=2) at test.cc:11
11	  return x;
(gdb) c
Continuing.
1 

Breakpoint 3, abs (x=14) at test.cc:16
16	   return( (x < 0L) ? -x : x);
(gdb) c
Continuing.
14 

Breakpoint 4, abs (x=-33.5) at test.cc:21
21	   return( (x < 0.0) ? -x : x);
(gdb) c
Continuing.
33.500000 
[Inferior 1 (process 12266) exited normally]
``
