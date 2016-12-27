# 動的ロードを行うサンプル

# ポイント
- dlsym, dlopenなどは癖があり、どのシンボルと結合するのかなどを意識する必要があるかも
 - ELF実行ファイルがどのように作られているのかなどは簡単に理解しておいたほうが良い。
- C++などでは少し呼び出しに特徴がある。

# 参考
- [Beginner's Guide to Linkers](http://www.lurklurk.org/linkers/linkers.html)
 - 非常に良い資料でリンカの仕組みやシンボルなどについての説明(CやC++などの違いも踏まえている。Windowsもあり)
- [Manpage of ld](https://linuxjm.osdn.jp/html/GNU_binutils/man1/ld.1.html)
