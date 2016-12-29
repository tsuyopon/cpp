# 動的ロードの場合のサンプル

# このディレクトリについて
- sample1
 - soを動的にロードするhelloworld的なプログラム
- sample2
 - dlopenしたsoの中からmain中に定義された関数を呼び出す場合
- sample3
 - dlopenしたsoの中から、mainと共有ライブラリ双方に同一の関数名が定義されている場合にどちらの関数を呼ぶかを決定す
- sample4
 - あとで呼ばれた共有ライブラリの中からそれ以前に呼ばれた共有ライブラリ中の関数を呼び出す
- sample5
 - weakシンボルを利用してdlsymなどで関数が実装されないパターンを考慮する
