# 概要
インライン展開の関数に対してgdbでブレークポイントを貼りたい場合

# 詳細
例えば、01などで最適化をかけてしまうとブレークポイントは貼ることができない。
```
$ g++ -O1 -g test.cc 
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/inline/a.out...done.
(gdb) b max
Function "max" not defined.
Make breakpoint pending on future shared library load? (y or [n]) y
Breakpoint 1 (max) pending.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/inline/./a.out 
answer is 5
[Inferior 1 (process 12503) exited normally]
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
```

最適化をしないO0オプションなどをかけることによってinline関数maxに対してブレークポイントを貼ることができるようになります。
```
$ g++ -O0 -g test.cc 
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/inline/a.out...done.
(gdb) b max
Breakpoint 1 at 0x40062c: file test.cc, line 4.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/inline/./a.out 

Breakpoint 1, max (a=3, b=5) at test.cc:4
4	  return a > b ? a : b;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) 
```
