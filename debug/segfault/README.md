SegmentationFaultをデバッグする
====

# 概要・設定

警告がでますがgccでビルドして実行ファイルを生成します。
```
$ gcc zeroDiv.c -o zeroDiv
zeroDiv.c: In function 'foo':
zeroDiv.c:3:17: warning: division by zero [-Wdiv-by-zero]
```

実行してみます
```
$ ./zeroDiv 
Floating point exception (core dumped)
```

/lib/libSegFault.so を使うと、わざわざ自分でシグナルハンドラをセットしなくても、 
環境変数 LD_PRELOAD をセットするだけで、異常終了時のバックトレースを表示できます。 
```
$ locate libSegFault.so 
/usr/lib64/libSegFault.so
$ export LD_PRELOAD=/usr/lib64/libSegFault.so
$ export SEGFAULT_SIGNALS=all 
```

再度実行するとデバッグ情報を出力してくれます。
```
$ ./zeroDiv 
*** Floating point exception
Register dump:

 RAX: 0000000000000005   RBX: 0000000000000000   RCX: 00000000004004f7
 RDX: 0000000000000000   RSI: 00007fffd6bf1d58   RDI: 0000000000000005
 RBP: 00007fffd6bf1c60   R8 : 0000003d549b1f40   R9 : 0000003d5420f310
 R10: 00007fffd6bf1ad0   R11: 0000003d54621640   R12: 00000000004003d0
 R13: 00007fffd6bf1d50   R14: 0000000000000000   R15: 0000000000000000
 RSP: 00007fffd6bf1c60

 RIP: 00000000004004f2   EFLAGS: 00010246

 CS: 0033   FS: 0000   GS: 0000

 Trap: 00000000   Error: 00000000   OldMask: 00000000   CR2: 00000000

 FPUCW: 0000037f   FPUSW: 00000000   TAG: 00000000
 RIP: 00000000   RDP: 00000000

 ST(0) 0000 0000000000000000   ST(1) 0000 0000000000000000
 ST(2) 0000 0000000000000000   ST(3) 0000 0000000000000000
 ST(4) 0000 0000000000000000   ST(5) 0000 0000000000000000
 ST(6) 0000 0000000000000000   ST(7) 0000 0000000000000000
 mxcsr: 1f80
 XMM0:  00000000000000000000000000000000 XMM1:  00000000000000000000000000000000
 XMM2:  00000000000000000000000000000000 XMM3:  00000000000000000000000000000000
 XMM4:  00000000000000000000000000000000 XMM5:  00000000000000000000000000000000
 XMM6:  00000000000000000000000000000000 XMM7:  00000000000000000000000000000000
 XMM8:  00000000000000000000000000000000 XMM9:  00000000000000000000000000000000
 XMM10: 00000000000000000000000000000000 XMM11: 00000000000000000000000000000000
 XMM12: 00000000000000000000000000000000 XMM13: 00000000000000000000000000000000
 XMM14: 00000000000000000000000000000000 XMM15: 00000000000000000000000000000000

Backtrace:
./zeroDiv[0x4004f2]
./zeroDiv[0x40050a]
/lib64/libc.so.6(__libc_start_main+0xf5)[0x3d54621735]
./zeroDiv[0x4003f9]

Memory map:

00400000-00401000 r-xp 00000000 fd:01 419469                             /home/tsuyoshi/git/cpp/binutils/addr2line/segfault/zeroDiv
00600000-00601000 rw-p 00000000 fd:01 419469                             /home/tsuyoshi/git/cpp/binutils/addr2line/segfault/zeroDiv
01fbe000-01fdf000 rw-p 00000000 00:00 0                                  [heap]
3d54200000-3d54220000 r-xp 00000000 fd:01 135298                         /usr/lib64/ld-2.15.so
3d5441f000-3d54420000 r--p 0001f000 fd:01 135298                         /usr/lib64/ld-2.15.so
3d54420000-3d54421000 rw-p 00020000 fd:01 135298                         /usr/lib64/ld-2.15.so
3d54421000-3d54422000 rw-p 00000000 00:00 0 
3d54600000-3d547ac000 r-xp 00000000 fd:01 135469                         /usr/lib64/libc-2.15.so
3d547ac000-3d549ac000 ---p 001ac000 fd:01 135469                         /usr/lib64/libc-2.15.so
3d549ac000-3d549b0000 r--p 001ac000 fd:01 135469                         /usr/lib64/libc-2.15.so
3d549b0000-3d549b2000 rw-p 001b0000 fd:01 135469                         /usr/lib64/libc-2.15.so
3d549b2000-3d549b7000 rw-p 00000000 00:00 0 
3d59200000-3d59215000 r-xp 00000000 fd:01 165445                         /usr/lib64/libgcc_s-4.7.2-20120921.so.1
3d59215000-3d59414000 ---p 00015000 fd:01 165445                         /usr/lib64/libgcc_s-4.7.2-20120921.so.1
3d59414000-3d59415000 rw-p 00014000 fd:01 165445                         /usr/lib64/libgcc_s-4.7.2-20120921.so.1
7f39da850000-7f39da853000 rw-p 00000000 00:00 0 
7f39da867000-7f39da86b000 r-xp 00000000 fd:01 135290                     /usr/lib64/libSegFault.so
7f39da86b000-7f39daa6a000 ---p 00004000 fd:01 135290                     /usr/lib64/libSegFault.so
7f39daa6a000-7f39daa6b000 r--p 00003000 fd:01 135290                     /usr/lib64/libSegFault.so
7f39daa6b000-7f39daa6c000 rw-p 00004000 fd:01 135290                     /usr/lib64/libSegFault.so
7f39daa6c000-7f39daa6d000 rw-p 00000000 00:00 0 
7fffd6bd2000-7fffd6bf3000 rw-p 00000000 00:00 0                          [stack]
7fffd6bff000-7fffd6c00000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]
Floating point exception (core dumped)
```


Backtrace情報から関数を表示します。
ファイル名と行番号は"??:0"になっていますが、-gオプションでビルドしてシンボル情報を付加すれば表示されるようになります。
```
$ addr2line -e zeroDiv -f 0x4004f2 0x40050a 0x3d54621735 0x4003f9
foo
??:0
main
??:0
??
??:0
_start
??:0
```

