# 概要
FUSE(Filesystem in User Spaceサンプルです。  
FUSEはユーザー空間で稼働するプログラムとしてファイルシステムを実装するための仕組みです。  
FUSEはLinuxカーネル2.6.14から利用可能な機能です。

# セットアップ
```
$ sudo yum install fuse-devel 
```

# hellofuse
makeするとhellofuseのバイナリが生成される。
あとはそれを使ってマウントする
```
$ mkdir mnt
$ ./hellofuse mnt 
$ ls -alt mnt/
total 4
drwxrwxr-x 3 tsuyoshi tsuyoshi 4096 Dec 29 08:23 ..
drwxr-xr-x 2 root     root        0 Jan  1  1970 .
-r--r--r-- 1 root     root       13 Jan  1  1970 hello
```

/mntの中にはhelloファイルが存在するのでこれをcatしてみる。
```
$ cat ./mnt/hello 
Hello World!
```

終了したらアンマウントする
```
$ fusermount -u mnt
```

# 参考
- (fuse reference)[https://lastlog.de/misc/fuse-doc/doc/html/hello_8c.html]
- (github libfuse)[https://github.com/libfuse/]
