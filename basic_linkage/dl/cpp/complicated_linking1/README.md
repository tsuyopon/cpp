# C++から動的ライブラリを呼び出す少し複雑なサンプル

# ポイント
- example1からはdlopenでhello.soとhello2.soを呼びます。
- hello2.soからはhello3.soをdlopenで呼びます。hello2.soのDT_NEEDEDにはlibexternal.soを加えています。

# 実行
コンパイルします
```
$ make
g++  -g -export-dynamic -shared -o hello.so hello.cpp -fPIC
g++  -g -export-dynamic -shared -o hello2.so hello2.cpp -fPIC -ldl
g++  -g -export-dynamic -shared -o hello3.so hello3.cpp -fPIC 
g++  -g -shared -o libexternal.so external.cpp -fPIC -Wl,-soname,libexternal.so
g++  -g -o example1 main.cpp -ldl -Wl,-rpath,'$ORIGIN' -L. -lexternal
```

gdbで実行してその際にtest.gdbinitをかまします。
ライブラリのロード処理を確認できます。
```
$ gdb ./example1 -x test.gdbinit 
Reading symbols from /home/tsuyoshi/git/cpp/basic_linkage/dl/cpp/complicated_linking1/example1...done.
Catchpoint 1 (load)
Catchpoint 2 (load)
Catchpoint 3 (load)
Catchpoint 4 (unload)
Catchpoint 5 (unload)
Catchpoint 6 (unload)
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/basic_linkage/dl/cpp/complicated_linking1/./example1 

C++ dlopen demo

Opening hello.so...

Catchpoint 1
  Inferior loaded ./hello.so
0x00007ffff7def53a in dl_open_worker () from /lib64/ld-linux-x86-64.so.2
Missing separate debuginfos, use: debuginfo-install glibc-2.17-292.el7.x86_64 libgcc-4.8.5-39.el7.x86_64 libstdc++-4.8.5-39.el7.x86_64
(gdb) c
Continuing.
Opening hello2.so...

Catchpoint 1
  Inferior loaded ./hello2.so
0x00007ffff7def53a in dl_open_worker () from /lib64/ld-linux-x86-64.so.2
(gdb) 
Continuing.
Loading symbol hello...
Calling hello...
hello2
Opening hello3.so...

Catchpoint 1
  Inferior loaded ./hello3.so
0x00007ffff7def53a in dl_open_worker () from /lib64/ld-linux-x86-64.so.2
(gdb) 
Continuing.

Catchpoint 4
  Inferior unloaded ./hello3.so
0x00007ffff7df04f1 in _dl_close_worker () from /lib64/ld-linux-x86-64.so.2
(gdb) 
Continuing.
Closing library...

Catchpoint 4
  Inferior unloaded ./hello2.so
0x00007ffff7df04f1 in _dl_close_worker () from /lib64/ld-linux-x86-64.so.2
(gdb) 
Continuing.

Catchpoint 4
  Inferior unloaded ./hello.so
0x00007ffff7df04f1 in _dl_close_worker () from /lib64/ld-linux-x86-64.so.2
(gdb) 
Continuing.
[Inferior 1 (process 6517) exited normally]
```

上記だけだとlibexternal.soの挙動が観測できないのでtest.gdbini中にLD_DEBUGとLD_DEBUG_OUTPUTが指定されていて、以下のファイルにそのログを出力します。
```
testlog.<pid>
```
