# 概要
cmakeを使ってみる

# 詳細
```
$ cmake .
-- The C compiler identification is GNU 4.7.2
-- The CXX compiler identification is GNU 4.7.2
-- Check for working C compiler: /usr/bin/gcc
-- Check for working C compiler: /usr/bin/gcc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/tsuyoshi/git/cpp/cmake
```

Makefile、CMakeCache.txt、CMakeLists.txt、cmake_install.cmakeのファイルやCMakeFilesのディレクトリが生成されていることがわかる。
```
$ ls -F
CMakeCache.txt  CMakeFiles/  CMakeLists.txt  Makefile  cmake_install.cmake  main.cpp
```

あとはMakefileが生成されているのでgmakeを実行するとCMakeLists.txtで指定された名前であるtestprogバイナリが生成されます。
```
$ gmake
-- Configuring done
-- Generating done
-- Build files have been written to: /home/tsuyoshi/git/cpp/cmake/hellosample
Scanning dependencies of target testprog
[100%] Building CXX object CMakeFiles/testprog.dir/main.cpp.o
Linking CXX executable testprog
[100%] Built target testprog
$ ls
CMakeCache.txt  CMakeFiles  CMakeLists.txt  Makefile  README.md  cmake_install.cmake  main.cpp  testprog
```
