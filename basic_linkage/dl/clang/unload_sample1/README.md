# 概要
dlcloseしてもsoがunloadされない場合がある。
- https://bugzilla.redhat.com/show_bug.cgi?id=1215452

# 実行
コンパイル
```
$ make
g++    -c -o main.o main.cpp
g++ -o test main.o -ldl -Wl,-R,'$ORIGIN'
g++ -fPIC -c -o so.o so.cpp
g++ -shared -o test.so so.o
```

実行するとtest.soをdlopenして、その後dlcloseした後なのにunloadされていません
```
$ ./test
7fb6629dd000-7fb6629de000 r-xp 00000000 fd:00 21287435                   /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/unload_sample1/test.so
7fb6629de000-7fb662bdd000 ---p 00001000 fd:00 21287435                   /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/unload_sample1/test.so
7fb662bdd000-7fb662bde000 r--p 00000000 fd:00 21287435                   /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/unload_sample1/test.so
7fb662bde000-7fb662bdf000 rw-p 00001000 fd:00 21287435                   /home/tsuyoshi/git/cpp/basic_linkage/dl/clang/unload_sample1/test.so
```
