# 概要
lvalueとrvalueについて  
C++98のreferenceは、C++0xにおいては、lvalue referenceと呼ばれるものである。

「オブジェクトの不要なコピーを抑えて、なるべく所有権(ポインタ)の移動だけで済ませよう」という仕組みがムーブセマンティクスでそれを実現するための仕組みがrvalue referenceという仕組みです。
これによって今までコピーしてlvalueをコンストラクタ等に渡していたものを、rvalueとしてコピーせずとも渡せるようになるということができます。

- lvalue
  - left hand value
- rvalue
  - right hand value

lvalueはアンパサンド1つ(&)で宣言し、rvalueはアンパサンド２つ(&&)で宣言する。  
lvalueはrvalueに変換できるが、その逆、rvalueをlvalueに変換することは出来ない(sample2.ccで確認すること)。

- lvalue
  - 寿命管理することができるオブジェクトを指す。
- rvalue
  - rvalueとは生まれた次の瞬間には死ななくてはならないオブジェクトのことなのです。X()など..
  - rvalue referenceとして受け取ったオブジェクト(例: A&& rr2 = A(); )はrvalueではなくて、lvalueということです。

std::moveの場合にはT::operator(T&& b)が呼ばれる仕組みになっているのでこの辺の違いをしっかりと理解しておく必要があります。

# 詳細
- sample1.cc
  - lvalueとrvalueを宣言だけするプログラム
- sample2.cc
  - rvalueかlvalueどちらかを判定するプログラム
  - lvalueはrvalueに変換できるが、逆はできないことを確認することができる。
- sample3_1.cc, sample3_2.cc
  - lvalueとrvalueを区別することによる利点を確認するためのプログラム
  - コンストラクタ内部で初期化した配列を別のオブジェクトにコピーコンストラクタですべてstd::moveしているが、rvalueによるmoveコンストラクタを利用するとポインタの付替えだけで済むようになる。
- sample3_3.cc
  - rvalueでポインタの付け替えができないかを確認するプログラム (このプログラムはコンパイル時に失敗することに注意)
- sample4.cc
  - 初期化でstd::vectorに約3000のrandomなデータをセットして、それらをソートするときの時間を測定するプログラム。これによりrvalueのコピーが以下に早いかがわかる
  - このプログラムには直接rvalueやlvalueが意識して使われていないが、コンテナでの格納で実際に高速であることが確認できる。(コンパイルオプションにstd=c++11などを付与するだけでこの恩恵を受けることができる)
  - 2つのバイナリが生成されるようにMakefileに記述されています。
- sample5.cc
  - is_rvalue_referenceを使って右参照かどうかをチェックする

# 参考URL
- rvalue reference 完全解説 
  - https://cpplover.blogspot.jp/2009/11/rvalue-reference_23.html
- What are move semantics?
  - http://stackoverflow.com/questions/3106110/what-are-move-semantics

# TODO
- もう少し深く

