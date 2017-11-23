# 概要
プロセスのメモリマッピングを確認する。

# コンパイル
コンパイルするとlayoutというプログラムが生成されます
```
$ make
$ ./layout
hello, (null): 0x0000000000000000
hello, not initialized global world: 0x0000000000600f20
hello, initialized global world: 0x0000000000600e40
hello, not initialized static world: 0x0000000000600ee0
hello, initialized static world: 0x0000000000600e80
hello, malloc world: 0x000000000174d010
hello, shared memory world: 0x00007f344d6bf000
hello, big malloc world: 0x00007f344d667010
hello, medium malloc world 1: 0x00007f344d646010
hello, medium malloc world 2: 0x000000000174d060
hello, local world: 0x00007fffccfd4000
```

引数を入れると最初の行が入る。
sharedmemoryやmallocはプログラムを再実行するとアドレスが変わってくる。今回は最初に実行したアドレスを元に解析していく。
```
$ ./layout hoge
hello, hoge: 0x00007fff2664a64c
hello, not initialized global world: 0x0000000000600f20
hello, initialized global world: 0x0000000000600e40
hello, not initialized static world: 0x0000000000600ee0
hello, initialized static world: 0x0000000000600e80
hello, malloc world: 0x0000000000d41010
hello, shared memory world: 0x00007f8843b72000
hello, big malloc world: 0x00007f8843b1a010
hello, medium malloc world 1: 0x00007f8843af9010
hello, medium malloc world 2: 0x0000000000d41060
hello, local world: 0x00007fff266495a0
```
自分の調査では引数を入れ忘れてしまった。

# 調査

プログラムを実行してみる。
```
$ ./layout
hello, (null): 0x0000000000000000
hello, not initialized global world: 0x0000000000600f20
hello, initialized global world: 0x0000000000600e40
hello, not initialized static world: 0x0000000000600ee0
hello, initialized static world: 0x0000000000600e80
hello, malloc world: 0x000000000174d010
hello, shared memory world: 0x00007f344d6bf000
hello, big malloc world: 0x00007f344d667010
hello, medium malloc world 1: 0x00007f344d646010
hello, medium malloc world 2: 0x000000000174d060
hello, local world: 0x00007fffccfd4000
```

参考までに今回実行した機種は64bitである。
```
$ uname -a
Linux localhost.localdomain 3.3.4-5.fc17.x86_64 #1 SMP Mon May 7 17:29:34 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
```

pmapでメモリ配置を確認する
```
$ pmap -x `pidof layout`
20287:   ./layout
Address           Kbytes     RSS   Dirty Mode   Mapping
0000000000400000       4       4       0 r-x--  layout
0000000000600000       4       4       4 rw---  layout
000000000174d000     132       8       8 rw---    [ anon ]
0000003897600000     128     108       0 r-x--  ld-2.15.so
000000389781f000       4       4       4 r----  ld-2.15.so
0000003897820000       4       4       4 rw---  ld-2.15.so
0000003897821000       4       4       4 rw---    [ anon ]
0000003897a00000    1712     272       0 r-x--  libc-2.15.so
0000003897bac000    2048       0       0 -----  libc-2.15.so
0000003897dac000      16      12       8 r----  libc-2.15.so
0000003897db0000       8       8       8 rw---  libc-2.15.so
0000003897db2000      20      12      12 rw---    [ anon ]
00007f344d644000     412      24      24 rw---    [ anon ]
00007f344d6bf000       4       4       4 rw-s-    [ shmid=0xe8002 ]
00007f344d6c0000       4       4       4 rw---    [ anon ]
00007fffccfb6000     132      12      12 rw---    [ stack ]
00007fffccfff000       4       4       0 r-x--    [ anon ]
ffffffffff600000       4       0       0 r-x--    [ anon ]
----------------  ------  ------  ------
total kB            4644     488      96
```

続いて/proc/<pid>/mapsも見てみる。
以下でinodeが0となっているセクションheap, stack, vdso, vsyscallとその他のpathnameが存在しないセクションはどのinodeにも紐付いていない。
これらはBSS(uninitialized data)を表しているものと思われる。
```
$ sudo cat /proc/`pidof layout`/maps
00400000-00401000 r-xp 00000000 fd:01 933203                             /home/tsuyoshi/git/cpp/memory/mapping_layout/layout
00600000-00601000 rw-p 00000000 fd:01 933203                             /home/tsuyoshi/git/cpp/memory/mapping_layout/layout
0174d000-0176e000 rw-p 00000000 00:00 0                                  [heap]
3897600000-3897620000 r-xp 00000000 fd:01 135298                         /usr/lib64/ld-2.15.so
389781f000-3897820000 r--p 0001f000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897820000-3897821000 rw-p 00020000 fd:01 135298                         /usr/lib64/ld-2.15.so
3897821000-3897822000 rw-p 00000000 00:00 0
3897a00000-3897bac000 r-xp 00000000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897bac000-3897dac000 ---p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897dac000-3897db0000 r--p 001ac000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db0000-3897db2000 rw-p 001b0000 fd:01 135311                         /usr/lib64/libc-2.15.so
3897db2000-3897db7000 rw-p 00000000 00:00 0
7f344d644000-7f344d6ab000 rw-p 00000000 00:00 0
7f344d6bf000-7f344d6c0000 rw-s 00000000 00:04 950274                     /SYSV00000000 (deleted)
7f344d6c0000-7f344d6c1000 rw-p 00000000 00:00 0
7fffccfb6000-7fffccfd7000 rw-p 00000000 00:00 0                          [stack]
7fffccfff000-7fffcd000000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
```

プログラムに紐付いているファイルをlsofで見てみる。先ほどinodeが存在しなかった箇所は表示されていない
```
$ lsof -p `pidof layout`
COMMAND   PID     USER   FD   TYPE DEVICE SIZE/OFF   NODE NAME
layout  20287 tsuyoshi  cwd    DIR  253,1     4096 933890 /home/tsuyoshi/git/cpp/memory/mapping_layout
layout  20287 tsuyoshi  rtd    DIR  253,1     4096      2 /
layout  20287 tsuyoshi  txt    REG  253,1     8745 933203 /home/tsuyoshi/git/cpp/memory/mapping_layout/layout
layout  20287 tsuyoshi  mem    REG  253,1   158440 135298 /usr/lib64/ld-2.15.so
layout  20287 tsuyoshi  mem    REG  253,1  2065552 135311 /usr/lib64/libc-2.15.so
layout  20287 tsuyoshi  DEL    REG    0,4          950274 /SYSV00000000
layout  20287 tsuyoshi    0u   CHR 136,11      0t0     14 /dev/pts/11
layout  20287 tsuyoshi    1u   CHR 136,11      0t0     14 /dev/pts/11
layout  20287 tsuyoshi    2u   CHR 136,11      0t0     14 /dev/pts/11
```

ELFの主要セクションサイズを確認する
```
$ size layout
   text    data     bss     dec     hex filename
   2487     752     160    3399     d47 layout
```

ELFサイズとどのセクションに配置されているのかを確認する。
この出力結果は後でメモリを図にするのに非常に役に立つ。
```
$ size --format=SysV -x layout
layout  :
section               size       addr
.interp               0x1c   0x400200
.note.ABI-tag         0x20   0x40021c
.note.gnu.build-id    0x24   0x40023c
.gnu.hash             0x1c   0x400260
.dynsym              0x108   0x400280
.dynstr               0x6d   0x400388
.gnu.version          0x16   0x4003f6
.gnu.version_r        0x20   0x400410
.rela.dyn             0x18   0x400430
.rela.plt             0xd8   0x400448
.init                  0xe   0x400520
.plt                  0xa0   0x400530
.text                0x4a4   0x4005d0
.fini                  0x9   0x400a74
.rodata               0x25   0x400a80
.eh_frame_hdr         0x3c   0x400aa8
.eh_frame             0xe4   0x400ae8
.init_array            0x8   0x600bd0
.fini_array            0x8   0x600bd8
.jcr                   0x8   0x600be0
.dynamic             0x1d0   0x600be8
.got                   0x8   0x600db8
.got.plt              0x60   0x600dc0
.data                 0xa0   0x600e20
.bss                  0xa0   0x600ec0
.comment              0x2c        0x0
Total                0xd73
```

以上のコマンド実行結果などを元にメモリ状況を図示すると次のようになる。
```

+------------------------------+  0x0000000000000000
:                              :
+------------------------------+  0x0000000000400000
|                              |  0x00000000004005d0(text開始)
|text                          |  機械命令
|                              |
+------------------------------+  0x0000000000401000
:                              :
+------------------------------+  0x0000000000600000
|                              |  0x0000000000600e20(data開始)
|data                          |  初期化された static 変数
|  initialized global var      |  0x0000000000600e40
|  initialized static var      |  0x0000000000600e80
|                              |
+------------------------------+  0x0000000000600ec0(bss開始)
|BSS                           |  初期化されていない static 変数
|  not initialized static var  |  0x0000000000600ee0
|  not initialized global var  |  0x0000000000600f20
|                              |
+------------------------------+  0x0000000000601000
:                              :
+------------------------------+  0x000000000174d000
|[heap]                        |  malloc() で動的に確保される領域(上位アドレスに伸びる)
|  malloc var                  |  0x000000000174d010
|  mediam malloc var2          |  0x000000000174d060
|                              |
+------------------------------+  0x000000000176e000
|             ||||             |
|             VVVV             |
:                              :
:                              :
|                              |
+------------------------------+  0x0000003897600000
|                              |
|  共有ライブラリ                |  (プログラム実行例だと３つほどの領域をつかっているがここでは省略)
|  (ld-2.15.so)                |
+------------------------------+  0x0000003897821000
|  ???                        |　  どのinodeにも紐付いていないので、ldライブラリ用のBSS(uninitialize data)データ?
+------------------------------+  0x0000003897822000
|                              |
+------------------------------+  0x0000003897a00000
|  共有ライブラリ                |  (プログラム実行例だと4つほどの領域をつかっているがここでは省略)
|  (libc-2.15.so)              |
+------------------------------+  0x0000003897db2000
|  ???                         |   どのinodeにも紐付いていないので、libcライブラリ用のBSS(uninitialize data)データ?
+------------------------------+  0x0000003897db7000
|                              |
:                              :
:                              :
|             ^^^^             |
|             ||||             |
+------------------------------+  0x00007f2eee98d000
|shared memory                 |  大きいサイズのmallocされた領域
|  mediam malloc var1          |  0x00007f344d646010
|  big malloc var              |  0x00007f344d667010
|                              |
+------------------------------+  0x00007f2eee9f3000
:                              :
+------------------------------+  0x00007f344d6bf000
|shared memory                 |  共有メモリ領域
|  shared memory var           |  0x00007f344d6bf000(上と同じ)
|                              |
+------------------------------+  0x00007f344d6c0000
| ???                          |   どのinodeにも紐付いていないので、shared memory用のBSS(uninitialize data)データ?
+------------------------------+  0x00007f344d6c1000
|                              |
:                              :
:                              :
|             ^^^^             |
|             ||||             |
+------------------------------+  0x00007fffccfff000
|[stack]                       |  関数呼び出しやローカル変数等で使用されるスタック領域(下位アドレスに伸びる)
|  local var                   |  0x00007fffccfd4000
|  arguments[1]                |  (今回はプログラムに指定し忘れてNULLになったが、本来はここらへんらしい)
|                              |
+------------------------------+  0x00007fffcd000000
:                              :
|                              |
|                              |
+------------------------------+  0x00007fffccfff000
|[vdso]                        |  vsyscallと同じ関数を提供するがvsyscallのように静的なアドレスが決定していない仕組み。
+------------------------------+  0x00007fffcd000000
:                              :
:                              :
|                              |
+------------------------------+  0xffffffffff600000
|[vsyscall]                    |  頻繁によびだされるようなシステムコール(gettimeofdayなど) 。静的アドレスが問題で通常はVDSOが使われる。
+------------------------------+  0xffffffffff601000
:                              :
:                              :
+------------------------------+  0xffffffffffffffff = 2^64 (64bit の場合)
```


# 参考URL
- [OS] 仮想メモリ空間のメモリマップを調べる
 - 非常に素晴らしいサイト。このサイトを元に調査してみた
 - http://th0x4c.github.io/blog/2012/10/10/os-virtual-memory-map/

