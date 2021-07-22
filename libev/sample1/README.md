# 概要
libev公式ドキュメントのサンプルに記載されていたものそのまま
- http://pod.tst.eu/http://cvs.schmorp.de/libev/ev.pod


# 仕様
このサンプルでは以下の2つのwatcherを利用している
- ev_io
- ev_timer

a.outを実行した後に以下の使用を満たすために使われている。
- ev_io: 入力があれば検知する
- ev_timer: a.out実行から5.5秒経過して何も入力が検知されなければ、「timeout」を出力して処理を終了する。
