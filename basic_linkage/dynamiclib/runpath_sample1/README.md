# RPATHではなく、RUNPATHを設定する。
最新だとDT_RUNPATHが推奨とされている。
しかし、互換性維持のためにRPATHは現状でも有効になっていることが多いらしい。

DT_RPATHはLD_LIBRARY_PATHよりも優先されるが、DT_RUNPATHはLD_LIBRARY_PATHの方が優先となっている。
ld.so(8)のManではDT_RPATHはdeprecated扱いとされている。

# ポイント
- コンパイル時にrpath指定の他にも--enable-new-dtagsを指定している。

# 実行
```
$ make execute
./sample
constructor
Hello, library world.
destructor
```

生成されたバイナリ中には-Wl,-rpathが指定されたにも関わらずRPATHは設定されていませんが、RUNPATHが設定されていることを確認できます。
```
$ objdump -x sample | grep -i rpath
$ objdump -x sample | grep -i runpath
  RUNPATH              $ORIGIN
```

# 参考
- https://linuxjm.osdn.jp/html/LDP_man-pages/man8/ld.so.8.html
  - DT_RPATH, DT_RUNPATH, LD_LIBRARY_PATHの参照優先順については上記ドキュメントに記載されている。
