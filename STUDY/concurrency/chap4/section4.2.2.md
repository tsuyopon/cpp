
# 4.2.2 condition valiableを用いてスレッドセーフなキューを作成する。

section3.2.3ではstd::stackコンテナについてみてきた。
今度はインスピレーションをわかせるためにListing4.2のstd::queueコンテナのInterfaceをみてみよう。

constructer, assignment, swapなどを無視すれば大別して次の３つにグループ分けできる。この分類はsection3.2.3でみたstd::stackと同じである。
これはsection3.2.3のstackコンテナのときと同等である。そして、この場合にも同じように固有のレースコンディションが存在する。 その結果として、front()とpop()を1つの関数で呼ぶ必要がある。
	・query
		empty(), size()
	・elements of queue
		front(), back()
	・modify the queue
		push(), pop(), emplate()

キューをスレッド間データ通信として利用する場合、受取側スレッドはデータをwaitする必要がある。
２つのパラメータとしてpop()として次の２つのvariantsを考える。
	try_pop(): 即座に返す(エラーならエラーを示す)
	wait_and_pop(): データが取得できるまで待つ


Listing4.3のようになる。
	consutroctorやassignmentはソースコードの単純化のための削減したものがListing4.3となります。
	deleteはコピーコンストラクタの明示的な禁止を表す。
		https://cpprefjp.github.io/lang/cpp11/defaulted_and_deleted_functions.html
	try_pop()とwait_and_pop()のオーバーロードがあることが確認できる。
	try_pop()の前者は参照値を引数で返し、戻り値としてstatusを返す。(see A.2)
		後者は前者とは異なり、ステータスを返すことはできないが、値を取得できなければNULLをセットすることができる。

Listing4.4を見てみることにする。
	これはListing4.1に関連している。Listing4.1からpush(), wait_and_pop()を抽出している。
	threadsafe_queueというクラスを作成してその中にグローバル変数だったmut, data_queue, data_cond及び、push(), wait_and_pop()を詰めている。

	1. このような実装にすることによって、Listing4.1ではmut, data_queue, data_condなど複数に分割していた変数がもはやthreadsafe_queueにすべて包括されることになる。
	2. notify_oneの同期が隠蔽されたので明示的に呼ぶ必要がなくなる。
	3. 状態変数としての変化を待つ

	wait_and_pop()にはwrite処理の若干のオーバーヘッドが残っている。


Listing4.5を見てみる。これが状態変数を利用したスレッドセーフクラスの最終型となっている。
	Listing4.4と比較をするとコンストラクタやwait_and_popの他のオーバロード関数、try_pop()、empty()などがthreadsafe_queueクラスに存在している。
	std::mutextのmut変数がmutableになっている。
		constなメンバー関数の中でも操作できるという意味を持つのがmutableの意味らしい。(もはやメンバー関数にconstを付与する意味がわからない...)

		http://soundengine.jp/wordpress/tips/tutorial/329/
		Listing4.4の例ではempty()というconstなメンバー関数中でmutexをlockする必要があり、そこでmutableな操作が必要となる。


	状態変数は複数スレッドがwaitしている場合にも役立つ、
		notify_one()を使えばどれか１つのスレッドに通知することができる。もしかしたらwaitせずに処理中なのかもしれないのでその場合は通知しないことも可能になる。


別の状態を考えてみる。複数のスレッドが同じイベントを待っている状態ですべてのスレッドを応答させたい場合。
これは共有データを初期化したような場合におこりうる。そして、スレッドが

# よくわからなかった表現
- If you take your lead for the signatures from the stack example, your interface looks like the following. (p72)




