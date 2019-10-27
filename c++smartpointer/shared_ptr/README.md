# 概要
shared_ptrは、複数のインスタンスが所有権を持てるスマートポインタです。
初期化する場合にはnewよりも(sample1.cc)、make_shared(sample2.cc)を使った初期化の方が推奨されます。

なお、shared_ptrでは配列をdelete[]としてうまく扱えない問題がありますので、make_sharedは使えませんのでその場合の方法をsample3.ccで扱っています。

