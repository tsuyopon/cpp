# 概要
C++での例外をキャッチする

# 詳細
とりあえずコンパイルして実行すると例外を出力するプログラムであることを確認する。
```
$ g++ -g3 -O0 test.cc 
$ ./a.out 
terminate called after throwing an instance of 'std::out_of_range'
  what():  basic_string::replace
Aborted
```

catch throwでキャッチしようとするとも最初に一度実行しておかないとnot definedとしなっているのでrunを一度実行する必要がある。
その後、「catch throw」をすると正しく登録されていることが確認できる。

runをして補足すると、バックトレースを補足することができる。
```
$ gdb -q ./a.out 
Reading symbols from /home/tsuyoshi/git/cpp/gdb/CatchException/a.out...done.
(gdb) catch throw
Function "__cxa_throw" not defined.
Catchpoint 1 (throw)
(gdb) run
Starting program: /home/tsuyoshi/git/cpp/gdb/CatchException/./a.out 
Catchpoint 1 (exception thrown), 0x00007ffff7b31c10 in __cxa_throw () from /lib64/libstdc++.so.6
Missing separate debuginfos, use: debuginfo-install glibc-2.17-260.el7.x86_64 libgcc-4.8.5-16.el7.x86_64 libstdc++-4.8.5-16.el7.x86_64
(gdb) catch throw
Note: breakpoint 1 also set at pc 0x7ffff7b31c10.
Catchpoint 2 (throw)
(gdb) run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/tsuyoshi/git/cpp/gdb/CatchException/./a.out 
Catchpoint 1 (exception thrown), 0x00007ffff7b31c10 in __cxa_throw () from /lib64/libstdc++.so.6
(gdb) bt
#0  0x00007ffff7b31c10 in __cxa_throw () from /lib64/libstdc++.so.6
#1  0x00007ffff7b86a97 in std::__throw_out_of_range(char const*) () from /lib64/libstdc++.so.6
#2  0x00007ffff7b927e0 in std::string::replace(unsigned long, unsigned long, char const*, unsigned long) () from /lib64/libstdc++.so.6
#3  0x00000000004008f0 in foo () at test.cc:14
#4  0x0000000000400896 in main () at test.cc:7
```

すばらしい

# 参考URL
- https://odz.hatenablog.com/entry/20070714/1184427916
