../soname_sample1と比較してみてください。ほとんど同じです。
違いとしてはsoname_sample1では実行時にLD_LIBRARY_PATHを環境変数として指定していましたが、これはバイナリコンパイル時にrpathに特別な変数$ORIGINを指定しています。

# 共有ライブラリにリンクしたアプリケーションを実行する際に、アプリケーションが存在するディレクトリを自動認識させることでライブラリ探索を容易にする

# ポイント
- rpathの指定に特別な変数$ORIGINを指定している

# 実行

今回は共有ライブラリなのでLD_LIBRARY_PATHを設定して実行するのでmake executeを利用します。
今回のサンプルではコンストラクタとデストラクタも動作するように追加しています(共有ライブラリだけの仕組みではありませんが)
```
$ make execute
./sample
constructor
Hello, library world.
destructor
```

rpathに$ORIGINと含まれた場合には、「アプリケーションが存在するディレクトリ」と特別な解釈を行います。
```
$ objdump -x sample | grep -i rpath
  RPATH                $ORIGIN
```

ソースコードからインストールされる場合には$ORIGIN/libなどに設定するとよさそうです。

# 参考
- https://linuxjm.osdn.jp/html/LDP_man-pages/man8/ld.so.8.html
