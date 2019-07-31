# 概要
C++でthisを使った場合のサンプルについて

# 詳細

- sample1.cc
  - thisのサンプル
- sample2.cc
  - thisのサンプル

以下の２つのプログラムはvimdiffで比較してみると良い
- class1.cc
  - 基底クラスからthis->test()を呼び出すが、必ず基底クラスのBase::test()が呼び出される意図しないパターン
- class2.cc
  - class1.ccの改良版。基底クラスからthis->test()を呼び出すが、派生クラスのXXXX::test()が呼び出されるパターン。
