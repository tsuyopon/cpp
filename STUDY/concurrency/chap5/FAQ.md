# 概要
5.2.4や5.2.5を調査していていろいろ思った疑問など

# FAQ

### atomicってのは結局mutexクラスを使うのと何が違うのだろうか?
次の違いがあるらしい
- atomic
  - 分割できない単位で表されるもので、半分だけ完了(half-done)の状態で観測することができないので一貫した状態を保ちます。
  - 最近のプロセッサではCAS(compare and swap)によって実現されている。
  - atomic操作は競合が比較的おきにくければ早い(他のスレッドにスイッチしてくれないので競合が発生するとatomic操作は不利になる)
  - たいていのプラットフォームではメモリバスをロックします。
- mutex
  - OSやライブラリなどのシステムによってリストを管理して必要なロック制御を行うことが多い
  - スレッド実行を停止して、他のCPUに対してCPUリソースを割り当てるので、スレッド切り替えに伴うコンテキストスイッチの負荷が大きい


- SeeAlso
  - https://stackoverflow.com/questions/15056237/which-is-more-efficient-basic-mutex-lock-or-atomic-integer

### mutex, atomic, semaphore, spinlock, volatileなどの違いはなんだったのだろうか?
mutexとatomicは上記で説明したので以下で説明する
- semaphore
  - ある資源が何個使えるかどうかを扱うための仕組みを提供する抽象データ型である。
- spinlock
  - 実装は様々だが一般的にはメモリーにロック中かどうかのフラグを用意し、そのフラグを使ってロック制御をする。
  - これを実行している間はスレッドは有益な仕事を何もせずに動作し続けるのでbusy-waitが発生する。
  - スレッドが短時間だけブロックされるのであれば、OSスケジューリングなどにも影響しないので、スピンロックは有効である。
- volatile
  - マルチスレッドについては全く考慮されない
  - volatileが解決する例
    - 局所的に無限ループと判断されてしまったが、別スレッドなどで変数が更新される可能性がる場合
    - https://qiita.com/YukiMiyatake/items/1191ab03b6c0b5a22876

### メモリバリアはなぜ必要なのか?

メモリバリアはmembar, memory fence, fence instructionなどとして知られている。

利用事例としてはプロセッサにおいて複数の前後関係が必要となる値が必要となる場合である。(Wikipedia: Memory barrierより引用)
このような場合にコンパイラで勝手に並び替え(reorder)しないように伝えるための仕組みである。

- processor1
```
 while (f == 0);
 // Memory fence required here
 print x;
```
- processor2
```
 x = 42;
 // Memory fence required here
 f = 1;
```

### メモリバリアの種類について
C++11ではこれだけある。
```
// C++11
enum memory_order {
  memory_order_relaxed, memory_order_consume, memory_order_acquire,
  memory_order_release, memory_order_acq_rel, memory_order_seq_cst
};
```

- memory_order_relaxed: スレッド間の順序付けの効果は一切持たない。
- memory_order_consume: acquire操作と似ているが、それより弱い順序付けでの読み込みを行うことを指示する。
- memory_order_acquire: acquire操作としての読み込みを行うことを指示する。store()など、書き込みのみを行う操作に対しては指定できない。
- memory_order_release: release操作としての書き込みを行うことを指示する。load()など、読み込みのみを行う操作に対しては指定できない。
- memory_order_acq_rel: 読み込みと書き込みを同時に行う操作(Read-Modify-Write操作)に対してのみ指定することができ、acquireとreleaseを合わせた効果を持つ。
- memory_order_seq_cst: acquire(読み込み操作の場合)、release(書き込み操作の場合)、acq_rel(Read-Modify-Write操作の場合)としての効果を持つ。

もっともコストが高いのがmemory_order_seq_cstだが速さを求めるC++としてはめずらしくこれがデフォルトらしい。

以下の記事によると
- http://yamasa.hatenablog.jp/entry/20090816/1250446250

x86/64アーキテクチャではmemory-orderingタグによってStoreやLoadの命令は次のインストラクションを使うらしい
```
Memory Ordering             Store              Load
--------------------------------------------------------
std::memory_order_relaxed    MOV [mem],reg      MOV reg,[mem]
std::memory_order_acquire    n/a                MOV reg,[mem]
std::memory_order_release    MOV [mem],reg      n/a
std::memory_order_seq_cst    XCHG [mem],reg     MOV reg,[mem]
```

memory_order_seq_cstを使わない場合の問題点については以下の資料でまとまっている。
- http://yamasa.hatenablog.jp/entry/20090816/1250446250

この資料もすごい良い。
- http://www.slideboom.com/presentations/83479/%E3%81%9D%E3%82%8D%E3%81%9D%E3%82%8Dvolatile%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6%E4%B8%80%E8%A8%80%E3%81%84%E3%81%A3%E3%81%A6%E3%81%8A%E3%81%8F%E3%81%8B

### メモリバリアに関するわかりやすい資料
以下のブログからリンクで貼ってある
- http://yamasa.hatenablog.jp/entry/20090720/1248085754

このスライド「そろそろvolatileについて一言いっておくか」が素晴らしすぎるのでそちらを参照のこと
- http://www.slideboom.com/presentations/83479/%E3%81%9D%E3%82%8D%E3%81%9D%E3%82%8Dvolatile%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6%E4%B8%80%E8%A8%80%E3%81%84%E3%81%A3%E3%81%A6%E3%81%8A%E3%81%8F%E3%81%8B

