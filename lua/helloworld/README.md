# 概要
luaを利用したサンプルプログラム


# 環境構築
手元のUbuntu-22.04で下記をインストール
```
$ sudo apt install lua5.4
$ sudo apt install liblua5.4-dev
```

コンパイルと実行
```
$ gcc -o test test.c -llua5.4 -lm -ldl -I/usr/include/lua5.4/
$ ./test 
Your Name: Azarashi
Hello!! Azarashi!
x: 9
y: 99
9 + 99 = 108
```

# 参考
- https://utakamo.com/article/lua/call-c-from-lua/index.html
