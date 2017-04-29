# 概要
キャストについて  

C++形式のキャストは次のようにして分類が４つに別れています。
- static_cast
  - 最初に試してみるべきキャストです。ポインタに関して厳しいだけの普通のキャストです。
    - この型変換の時、実行時に自動的に安全性を確認することはありません。例えば int の値を char に代入するときに桁あふれするかどうかとか、ダウンキャストの時にそれは安全なのかとかです。
    - ただ、実行しなくても危険な変換だと分かるときはコンパイルエラーになります。例えば、ポインタから int への変換、int からポインタへの変換、int へのポインタから double へのポインタへの変換、全く関係ないクラスへのポインタ同士の型変換などがそうです。
- const_cast
  - constやvolatileを除去するためのキャスト
  - これらの修飾子を外すためのキャストなので本来使うべきキャストではないが、古いライブラリなどで利用される
- dynamic_cast
  - 基底クラスから派生クラスへのキャスト(downcast)を対象とする。なおupcastも可能だがstatic_castが推奨らしい。
- reinterpreter_cast
  - 他のキャストが利用できない場合の最終手段となるキャスト
  - ポインタ同士のキャストやポインタと整数型のキャストなどを対象とする

以下の資料も参考にすること
- http://d.hatena.ne.jp/kasei_san/20080319/p1

# 参考
- http://stackoverflow.com/questions/332030/when-should-static-cast-dynamic-cast-const-cast-and-reinterpret-cast-be-used
- http://www.geocities.jp/bleis_tift/cpp/newcast.html
- http://d.hatena.ne.jp/kasei_san/20080319/p1
