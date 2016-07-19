# C++から呼び出すサンプル

# ポイント
- 呼び出す関数に「extern "C" { ... }」が付与されています。これによりCから呼び出せるようにしています。
 - C++ではシンボルがマングリングされるので、C言語からだと呼び出せないのでそれを明示的に伝える仕組みです。

# 実行
makeして実行するだけです
```
$ make
g++  -export-dynamic -shared -o hello.so hello.cpp -fPIC
g++  -o example1 main.cpp -ldl
$ ./example1 
C++ dlopen demo

Opening hello.so...
Loading symbol hello...
Calling hello...
hello
Closing library...
```

