# 概要
ACQUIRE-RELEASE ORDERING(p132-p136)

# 説明
relax orderingを強化したものには次のようなものが存在します。
- atomic loadsはaquire操作　(memory_order_acquire)
- atomic storeはrelease操作 (memory_order_release)
- atomic read-modify-write操作 (std::atomic::fetch_add(), std::atomic::exchange()) はaquire, releaseどちらか, または両方memory_order_acq_rel

5.4の改良として5.7がある。
5.4ではstd::memory_order_seq_cstをオプションとして指定していて決してassertが実行されませんでした。
しかし、5.7のケースではassertが実行されてしまう可能性を秘めています。

なぜならば、xとy両方ともfalseとして読み込まれることが可能があります。xとyは異なるスレッドによって書き込みが行われていることが原因です。
Figure5.6はListing5.7からのhappens-before関係を示している

```
Happens Beforeについて
	Thread Aで実行されるソースコード箇所aが
	Thread Bで実行されるソースコード箇所bよりも常に先に実行すべきということであるのであれば、
	aとbはhappens before関係にあるという。

	Happens Beforeは同一スレッドでは成り立つが、異なるスレッドではHappens Beforeは成り立たない。
```

aquire-release orderingの利点を得るためにはどうすれば良いか?
- 2つの変数のstoreを同一スレッドから行なうことを考慮する必要がある。 
- yのstoreをmemory_order_releaseで指定して、yのload処理をmemory_order_acquireとすることでxの実行順序を制御することができる。-> Listing5.8を参照のこと
```
memory_order_releaseとmemory_order_acquireの説明
	memory_order_release は「それより前の全ての文」に対して順序付けを保証する(先行する命令が後ろにリオーダーされるのを防ぐ)
	memory_order_acquire は「それより後の全ての文」に対して順序付けを保証する(後述の命令がバリアを超えて前にリオーダーされるのを防ぐ)
```

マルチスレッドで特に気をつけるべき罠としては次の点に注意すると良い
- (参考) https://www.slideshare.net/KMC_JP/c-47378581
  - ・1. 読み書きの競合
  - ・2. キャッシュによる一貫性の変化
  - ・3. コンパイラによる最適化
- Listing5.7の場合だと2で引っかかる可能性があるケース!?

# まとめ
- memory_order_releaseとmemory_order_acquireを使った処理の場合にはHappens Beforeが成り立たなくなる場合があることを理解しておく
- memory_order_releaseとmemory_order_acquireを利用する場合には、memory_order_acq_relの場合とは異なりスレッド間で実行される順序付け(コア間でのデータの同期状態)を保証するには１つのスレッドで2つの変数のstore処理を行わなければならない。


# 参考資料
- キャッシュコヒーレンシ理解のために資料を漁ったら昔のスライドが出てきたので公開する
  - http://msyksphinz.hatenablog.com/entry/2016/04/07/024623
  - https://www.slideshare.net/masayukikimura520/4-60571864
- キャッシュコヒーレンシ
  - 連載もすごい多い。
  - https://news.mynavi.jp/article/architecture-184/
