# メモリリークによりdlcloseでunloadされないサンプル
この例ではsqlite3を用いています。sqlite-develパッケージをインストールしておいてください。
```
$ sudo yum install sqlite-devel
```

### ポイント
- subhello.cとgreeding.cの中でメモリリークするようにsqlite3_openを両方で呼び出しています。

### 詳細
以下のgdbデバッグからわかるようにsubhello.soがunloadされていません

```
(gdb) catch load
Catchpoint 1 (load)
(gdb) catch unload
Catchpoint 2 (unload)
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/unload_sample2/main 

Catchpoint 1
  Inferior loaded /lib64/libdl.so.2
    /lib64/libc.so.6
dl_main (phdr=<optimized out>, phdr@entry=0x400040, phnum=<optimized out>, phnum@entry=9, user_entry=user_entry@entry=0x7fffffffe308, auxv=<optimized out>) at rtld.c:2282
2282	  LIBC_PROBE (init_complete, 2, LM_ID_BASE, r);
(gdb) c
Continuing.

Catchpoint 1
  Inferior loaded ./hello.so
dl_open_worker (a=a@entry=0x7fffffffe048) at dl-open.c:556
556	    LIBC_PROBE (reloc_complete, 3, args->nsid, r, new);
(gdb) 
Continuing.
Hello, 200
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".

Catchpoint 1
  Inferior loaded ./subhello.so
    /lib64/libsqlite3.so.0
    /lib64/libpthread.so.0
dl_open_worker (a=a@entry=0x7fffffffe028) at dl-open.c:556
556	    LIBC_PROBE (reloc_complete, 3, args->nsid, r, new);
Missing separate debuginfos, use: debuginfo-install sqlite-3.7.17-8.el7_7.1.x86_64
(gdb) 
Continuing.
subhello
From main: 201

Catchpoint 1
  Inferior loaded ./greeding.so
dl_open_worker (a=a@entry=0x7fffffffe048) at dl-open.c:556
556	    LIBC_PROBE (reloc_complete, 3, args->nsid, r, new);
(gdb) 
Continuing.
Hello, 1
subhello
GoodbyeGood Morning

Catchpoint 2
  Inferior unloaded ./greeding.so
_dl_close_worker (map=map@entry=0x614ef0) at dl-close.c:746
746	  LIBC_PROBE (unmap_complete, 2, nsid, r);
(gdb) 
Continuing.

Catchpoint 2
  Inferior unloaded ./hello.so
_dl_close_worker (map=map@entry=0x602030) at dl-close.c:746
746	  LIBC_PROBE (unmap_complete, 2, nsid, r);
(gdb) c
Continuing.
[Inferior 1 (process 4617) exited normally]
```
