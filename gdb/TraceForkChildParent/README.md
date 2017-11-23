# 概要
forkを追跡するようなプログラムの場合に次のようなパターンがあります。
- (1) childを追跡する
- (2) parentを追跡する

ここではそれぞれの方法について説明します

# 詳細

test.cのプログラム中でparentかchildかなどでswitch分岐されますので、正しく追跡できているのかを確認します。

### (1) childを追跡する
「set follow-fork-mode child」というモードを実行するとchildを追跡します。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/fork/a.out...done.
(gdb) b test.c:8
Breakpoint 1 at 0x400591: file test.c, line 8.
(gdb) b test.c:11
Breakpoint 2 at 0x4005a5: file test.c, line 11.
(gdb) b test.c:14
Breakpoint 3 at 0x40059b: file test.c, line 14.
(gdb) set follow-fork-mode child
(gdb) r
Starting program: /home/tsuyoshi/cpp/gdb/fork/./a.out 
[New process 14461]
[Switching to process 14461]

Breakpoint 2, main () at test.c:11
11			break;
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) list
6		{
7		  case -1:
8			exit(1);
9		  case 0:
10			//child process,continue
11			break;
12		  default:
13			//the current process,exit
14			exit(0);
15		}
(gdb) c
Continuing.
[Inferior 2 (process 14461) exited normally]
```

### (2) parentを追跡する

「set follow-fork-mode parent」を実行する、もしくはデフォルトではparent追跡モードとなります。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/cpp/gdb/fork/a.out...done.
(gdb) b test.c:8
Breakpoint 1 at 0x400591: file test.c, line 8.
(gdb) b test.c:11
Breakpoint 2 at 0x4005a5: file test.c, line 11.
(gdb) b test.c:14
Breakpoint 3 at 0x40059b: file test.c, line 14.
(gdb) run
Starting program: /home/tsuyoshi/cpp/gdb/fork/./a.out 
Detaching after fork from child process 14468.

Breakpoint 3, main () at test.c:14
14			exit(0);
Missing separate debuginfos, use: debuginfo-install glibc-2.17-196.el7.x86_64
(gdb) list
9		  case 0:
10			//child process,continue
11			break;
12		  default:
13			//the current process,exit
14			exit(0);
15		}
16	}
(gdb) c
Continuing.
[Inferior 1 (process 14464) exited normally]
```

上記の例では以下が実行されておらずデフォルト仕様を使っています。必要に応じて以下のコマンドを実行してください。
```
(gdb) set follow-fork-mode parent
```


# 参考URL
- https://stackoverflow.com/questions/6199270/how-do-i-debug-the-child-process-after-fork-in-gdb
