# 概要
cppunitの最小構成パッケージ


# 使い方
基本的にはmainプログラム(test_runner.cpp), テストプログラム(test_template.cpp)の２つを同時に同じディレクトリ中に配置する。
- test_runner.cppは特に修正不要で問題ない
- test_template.cppはテストプログラムのサンプルプログラム。複数テストを配置する場合にもこのファイルをテンプレートとしてコピーすれば良い。

Makefile中に.cpp拡張子であれば自動的にテストをコンパイルして、組み込むようになっています。

# コンパイル

```
$ sudo yum install cppunit-devel
$ make
$ make test
$ make distclean
```

# 参考
- https://blog.mafr.de/2006/12/13/testing-c-apps-using-cppunit/
