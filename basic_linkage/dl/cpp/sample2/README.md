# dlsymからC++のクラスを呼び出すサンプル
C++クラスをdlsymなどから呼び出す場合にはちょっとトリッキーな方法が必要となります

# ポイント
- C++から呼び出されるC++クラスのインスタンスをnewするクラスとクラスをdeleteするクラスをextern "C"で準備している

# 実行
makeして実行するだけです
```
$ make
g++  -export-dynamic -shared -o triangle.so triangle.cpp -fPIC
g++  -o example2 main.cpp -ldl
$ ./example2 
The area is: 42.4352
```

# 参考
- [HOWTO](http://www.tldp.org/HOWTO/html_single/C++-dlopen/)
