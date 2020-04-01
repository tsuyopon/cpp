# 概要
cppunit + lcovまでを用いたパッケージです。

このディレクトリにHoge.ccとHoge.hというライブラリを配置して、testsディレクトリ内部からそのライブラリのテストを実行しています。
さらにlcovによるカバレッジレポートの表示を行なっています。

# インストール
以下のパッケージインストール作業を行なっておいてください。
```
$ sudo yum install cppunit-devel lcov
```

# 使い方

```
$ cd tests
$ make
$ make cov
```
以上によりテストの実行とcoverage生成までを行います。

# 参考
- https://blog.mafr.de/2006/12/13/testing-c-apps-using-cppunit/
