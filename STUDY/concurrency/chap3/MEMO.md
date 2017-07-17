# 勉強メモ

### 3.2.6 std::unique_lockを使った柔軟なロックについて

- std::unique_lockはstd::lock_guardよりも柔軟である。
- コンストラクタ生成時点では常にmutexを所有しているわけではない(後で述べるstd::defer_lockが存在するから)

- std::unique_lockの第２引数として指定できるもの
  - std::adopt_lockは所有権を移譲する
  - std::defer_lockはコンストラクタ呼び出し時には取得せずに、lockで取得する。

- コードの記述例はListing3.6からListing3.9に書き換えを行なったもの。
  - std::lock_guard and std::adopt_lock を　std::unique_lock and std::defer_lockに書き換える前のコードと等価である。

- std::unique_lockはlock(), try_lock(), unlock()などを提供する。
  - 現在所有されているかどうかというフラグも存在する。
    - このフラグはowns_lock()で参照することができるようになる。
  - 所有されていたらdestructorでunlock()が呼ばれ、所有されていなかったらunlock()は呼ばれない。

- std::unique_lockの方がstd::lock_guardよりも次の欠点がある
  - サイズが大きなオブジェクトとなる
  - フラグの更新やチェックなどの機能も持つので処理はstd::unique_lockの方が若干のパフォーマンス上のpenaltyがある。


英文解釈できなかった英文
```
・Listing 3.6 could just as easily have been written as shown in listing 3.9,　　 // 3.6を3.9にみられるように書き換えるのは簡単なことです。 
・The flexibility of allowing a std::unique_lock instance not to own the mutex comes at a price
```

### 3.2.7  スコープ間でmutex所有権を移譲する

- 次のようにしてmutexの所有権を移動させることができる。
  - 関数から戻るとき
  - 明示的にstd::moveを呼び出すとき

呼び出しはlvalueやrvalueの定義に依存する。
- lvalue: リファレンス (明示的に行われる必要がある。アクシデントをさけるため。&で宣言する)
- rvalue: temporary  (automaticに変換される。&&で宣言する)

もっともよくあるのは関数にmutexをロックさせることを許し、呼び出し元にそのmutexの所有権を移譲する方法
```
	std::unique_lock<std::mutex> get_lock()
	{
	    extern std::mutex some_mutex;
	    std::unique_lock<std::mutex> lk(some_mutex);
	    prepare_data();
	    return lk;                       // コンパイラが自動的にstd::moveとして取り扱う!???
	}
	void process_data()
	{
	    std::unique_lock<std::mutex> lk(get_lock());
	    do_something();
	}
```

- 参考
  - https://stackoverflow.com/questions/26014368/c11-move-when-returning-a-lock
  - https://stackoverflow.com/questions/4986673/c11-rvalues-and-move-semantics-confusion-return-statement?noredirect=1&lq=1
  - http://d.hatena.ne.jp/gintenlabo/20110125/1295991902

上記のlkはstd::move(lk)を返却しているとのことですが、
正確に言うと、コンパイラが NRVO によってコンストラクタ呼び出しを省略していい場合
つまり、関数の戻り値と（CV修飾子まで）同じ型の、参照でないローカル変数 x を、そのまま return x; と返す場合には、そのオブジェクト x は、 rvalue として扱われます。

この最適化が働くと、「無用だと思われるコピーコンストラクタ」をコンパイラが削除します。 （削除しても「いいよ」ということになっています。あくまでもコンパイラ実装依存）

- std::unique_lockはdestructer前に放棄することもできる。これはunlockを使うことによって可能である。
- 必要以上にロックを保持することは、他のスレッドが待たされることになるので著しいパフォーマンスの低下を及ぼす。


### 3.2.8 適切な粒度でロックをかける
- 小さなデータは細かい単位でロックをかけて、大きなデータは大きなデータ単位でロックをかける。
- 複数スレッドが同一リソースに対して待機状態であり、１つのスレッドが必要以上にロックを持つようであれば、全体としても待ち時間の増加につながる。
- 可能ならばロックしている範囲外で処理を行うようにするのがよい。
  - 特にロックを抱えている最中にファイルI/Oのような時間を消費する処理を行ってはならない。
  - ファイルI/Oは同様のサイズのメモリ読み書きと比較して、何百倍も遅い。
  - std::unique_lockを使うと処理がかかる手前でunlock()して、(ロックが不必要な)処理が終わり次第lock()をかける
```
void get_and_process_data()
{
    std::unique_lock<std::mutex> my_lock(the_mutex);
    some_class data_to_process=get_next_data_chunk();
    my_lock.unlock();                                  // 1. 次の処理はロックが必要ないので一旦unlock()
    result_type result=process(data_to_process);
    my_lock.lock();                                    // 2. ロックが必要な処理になるので再びlock()
    write_result(data_to_process,result);
}
```

- データ量における粒度だけがmutex対象というわけではなく、「どれだけの間ロックされるのか?」、「ロックされた時に何の操作が行われるのか?」といったことを考慮する必要がある。

- Listing3.10により全体をlockしないことによってもしかしたら２つが交換されているかもしれない。つまり意味のない比較を行っている。
- 全体をロックしないということはレースコンディションにさらされている 

