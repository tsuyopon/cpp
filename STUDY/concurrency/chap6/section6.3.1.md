# 6.3 Designing more complex lock-based data structures (より複雑なロックが必要となるデータ構造を設計する)

スタックやキューはシンプルです。
つまり、IFは極めて制限されていて、それらは特定の目的に対してしっかりとフォーカスされています。
すべてのデータ構造がシンプルというわけではありません。ほとんどのデータ構造は様々な操作を可能にしています。原則として、これらはconcurrencyへの大きな機会を与えています。
しかし、その機会は複数でのアクセスパターンが考慮に含まれるために、データを保護するタスクをより困難にします。 
振舞われる様々な操作の正確な性質というものはconcurrencyなアクセスのデータ構造を設計するときに重要となります。

## 6.3.1 Writing a thread-safe lookup table using locks (ロックを使ってスレッドセーフなロックアップテーブルを記述する)

ルックアップテーブルやディクショナリは、keyとmappedされた値で結びつきます。    
一般的にはそのようなデータ構造の裏にある意図としては、与えられたキーに関連付けられたデータを要求するコードを許容することです。  
C++標準ライブラリではこの機能はstd::map<>, std::multimap<>, std::unordered_map<>,　std::unordered_multimap<> のようなコンテナで提供されています。
ルックアップテーブルはstackやqueueと比較して使用パターンが異なります。  
stackやqueue上のほとんどすべての操作は要素を追加するか・要素を削除するかという修正が行われる一方で、ルックアップテーブルというのは滅多に修正が発生しません。

listing3.13の単純なDNS Cacheはそのようなシナリオ例の１つです。std::map<>と比べてはるかに削減されたI/Fが特徴となっています。

stackやqueueで見られるように、データ構造は複数スレッドでconcurrentにアクセスされることになっているときに標準コンテナのInterfaceは適切ではないです。
なぜなら、インターフェース設計においては固有のレースコンディション状態あるので、それらを取り除く必要があります。

concurrencyからみたstd::maps<>インタフェースが持つ最も大きな問題というのは、イテレーションである。

他のスレッドがコンテナへアクセスしたり修正したりする際に、コンテナへの安全なアクセスを提供するというイテレータを持つことは可能であるけれども、これはトリッキーな命題である。
正しくイテレータを扱うことは、イテレータが参照していると要素の削除をしている他のスレッドのような問題を扱わなければならないということ意味します。
スレッドセーフなルックアップテーブルI/Fを最初に作成するために、イテレータをスキップできるでしょう。

std::map(や他の標準ライブラリの連想コンテナ)のインターフェースがイテレータによって大部分がベースとなっていることを考慮すると、それらのコンテナは別においておいて、地盤から設計することを選択する方が価値がありそうです。

テーブルをルックアップする際には次のような操作があります。
- 新しいkey/valueを追加する
- 与えられたkeyに対するvalueを変更する
- key/valueを削除する
- 必要あれば、与えられたkeyに対する値を取得する。

コンテナには操作に役立つものがあります。コンテナが空かどうかのチェックや、keyリストの完全なスナップショットの提供、key/valueペアの完全なスナップショットの提供などです。  

もし、あなたが参照は返さない、各メンバー関数の全体にmutex lockを配置したりするなどシンプルなスレッドセーフガイドラインに従うのであれば、これらはすべて安全です。

レースコンディションへの最大限の可能性がおこりうるのは、key/valueペアが追加されるときです。
もし、２つのスレッドが新しいvalueを追加した場合、最初の１つだけが可能で、２番目は失敗するでしょう。

１つの可能性は、listing3.13のDNS cacheでみられたように追加と変更を１つのメンバー関数に含めてしまうことです。  


interfaceの観点からのその他の興味深い点としては、
１つのオプションは、keyが存在しなかった場合のケースとしての戻り値としてユーザーに"default"値を提供することです。
```
mapped_type get_value(key_type const& key, mapped_type default_value);
```

もしdefault_valueが明示的に与えられなかったら、このケースではデフォルトコンストラクタとして生成されたインスタンスのmapped_typeが使われる。

これは単純にmapped_typeのインスタンスの代わりにstd::pair<mapped_type, bool>を返却する拡張である。boolはvalueが存在しているかどうかを示しています。  
他のオプションとしては、値を参照するスマートポインタを返却することです。  
もしポインタの値がNULLであれば、戻すべき値が存在しないということを意味しています。  

すでに述べたように、一度interfaceが決定したら、スレッド安全はデータ構造に基づいて保護するためにすべてのメンバー関数の周りに1つのmutexをしたり、単純なロックによって保証されていると思います。

しかしながら、これはデータ構造の読み込みや修正のための関数の分割によって提供されるconcurrencyの可能性を無駄遣いしていることにもなりうります。

１つのオプションはlisting3.13に記載されたboost::shared_mutexのように複数のreader threadsをサポートした、１つのwriter threadをサポートしているmutexを使うことです。

これによってconcurrencyなアクセスを改善し、1つのスレッドだけがデータ構造を修正することができる。

(追記)
- Example for boost shared_mutex (multiple reads/one write)?
  - https://stackoverflow.com/questions/989795/example-for-boost-shared-mutex-multiple-reads-one-write

boost::shared_mutexの利用方法は次のような感じになる。
```
boost::shared_mutex _access;

// readerの場合にはshared_lockを利用する。
void reader()
{
  // get shared access
  boost::shared_lock<boost::shared_mutex> lock(_access);

  // now we have shared access
}

// upgrade_lock -> upgrade_to_unique_lockの順番で取得する必要がある。ここで取得するロックは「同時に一つしか取れない特別なread lock」を意味する。
void writer()
{
  // get upgradable access
  boost::upgrade_lock<boost::shared_mutex> lock(_access);

  // get exclusive access
  boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueLock(lock);

  // now we have exclusive access
}
```


### DESIGNING A MAP DATA STRUCTURE FOR FINE-GRAINED LOCKING  (細かいロックのためのmapデータ構造の設計)

section6.2.3で議論されたqueueと同様に、細かいロックを許可するためにあなたはstd::map<>のような既存コンテナをただラッピングするのではなく、データ構造の詳細を注意深く確認する必要があります。


次の様にルックアップテーブルのような連想コンテナを実装するには３つの共通した方法があります。
- バイナリツリー (赤黒木のような)
- 配列
- ハッシュテーブル

(追記) 赤黒木アルゴリズムについては、次の資料がわかった気になれた。
- Red-Black Tree by Java -- これで分かった赤黒木
  - http://wwwa.pikara.ne.jp/okojisan/rb-tree/index.html
- MAP
  - https://www.slideshare.net/kikairoya/map-17091504

バイナリツリーはconcurrencyのための拡張機会を十分には提供してくれません。
すべてのlookupや修正はroot nodeから開始することによってアクセスしなければならない。root nodeもそれゆえにlockが必要となります。
このlockはスレッドがnodeを下へと移動していく際に解放されるが、全データ構造に対するシングルロックよりも良くない。  

配列はさらに悪くなります。なぜなら、与えられたデータが配列中のどこに格納されるのか前もってわからないからです。それゆえに、全配列に対してシングルロックが必要となってきます。  

最後にハッシュテーブルです。
bucket(入れ物)における固定値だと仮定されるので、keyはそのkeyに純粋に結びつけられています。(ちょっと英訳が..)
これはbucketごとに安全な分割されたロックを持つことができることを意味します。
もし、multiple readerやsingle writerをサポートしているというmutexを再度使った場合、N-foldであるconcurrency(Nはbucket数)の機会を増加させることができます。
欠点としてはkeyに対する良いハッシュ関数を利用する必要があるということです。
C++標準ライブラリはstd::hash<>テンプレートを提供しています。このテンプレートは良いハッシュ関数を利用する目的として利用することができます。

そしてユーザーは簡単に他のkey typeへと特化させることができます。

もし、標準の整列されていないコンテナ(unorderd containers)を利用したり、テンプレートパラメータとしてハッシュ化するために関数オブジェクトのtypeを受け取るのであれば、ユーザーはそれらのkey typeのために特化したstd::hash<> や ハッシュ関数の分割を提供するかどうかを選択することができます。 (XXX: 意味がよくわかっていない...)

じゃあ、いくつかのコードを見てみましょう。
スレッドセーフなlookup tableの実装はどうなっているのか? 1つの可能性としていかに記載されています。

[listin6.11のコード|listing6.11.cc]

この実装ではbucketsをholdするためにstd::vector<std::unique_ptr<bucket_type>> (6)を使っています。これはコンストラクタで指定されたbucket数を許容します。デフォルトではその数値は19で素数です。
ハッシュテーブルはbucketsが素数の際によく動きます。
- 参考: https://qiita.com/hikaru-light/items/6b6958a6aaa5bfb96a87

それぞれのbucketsは1つのバケットに対してconcurentなread処理やmodificationを許容するためにboost::shared_mutexインスタンス(1)で保護されています。
bucketの数は固定値なので、get_bucket関数(7)はロックなしで呼ばれます(8, 9, 10)。
TODO: 固定値だとなぜロックなしなのか不明

そして、それからbucket mutexは各関数で適切にshared ownership(read-only) (3) かunique(read/write) ownership (4, 5)としてロックされます。

すべての３つの関数はバケット内にエントリがあるかどうかを決定するためにfind_entry_for()メンバー関数(2) を最大限に利用します。  
それぞれのbucketはstd::listのkey/valueペアを含みます。エントリの追加や削除は簡単です。  

すでにconcurrencyに関してはカバーしてきた、そして、すべては適切にmutexロックで保護してきましたが、例外安全についてはどうだろうか?
value_for関数は何も修正しないので、問題ありません。
もし、value_forが例外を投げていたとしても、データ構造には影響ないでしょう。

remove_mapping関数はeraseコールを利用してlistを修正します。これはthrowしないことが保証されていますので、これも安全です。  
残るはadd_or_update_mapping関数ですが、2つの分岐のうちの片方でif.push_backがthrowを投げるかもしれませんが例外安全です、もしthrowされた場合にもオリジナルの状態のlistは残ります。よって、これらの場合にも問題ありません。  

1つの問題としてはあなたが現行の値を置き換える場合のケースにおける割り当てです。
もし割り当てが例外をthrowしたら、オリジナルが変化していないことに頼ることになります。
しかしながら、これは全体としてデータ構造には影響を与えず、ユーザーが与えたタイプのpropertyとなります。 よって、ユーザーにこの扱いをまかせてしまうことが安全です。
TODO: 上記の文章の意図がわからない。

このセクションのはじめで、例えばstd::map<>の例の様にルックアップテーブルで持つと良い素敵機能としては現在の状態のsnapshotを取得できるオプションについて述べた。  
これは、整合性を保った状態のコピーを保証するために順番で全コンテナへのロックを必要とします。

なぜならば、通常のルックアップテーブルに対する操作というもは1度に1つのbucketのみを要求しますが、この場合にはすべてのbucketへロックを要求する唯一の操作になるでしょう。

それゆえに、あなたが毎回同じ順番でロックするという条件下においては、デッドロックの可能性はないでしょう。そのような実装は以下のListing6.12になります。

```
// Listing6.12: Obtaining contents of a threadsafe_lookup_table as a std::map<>

std::map<Key,Value> threadsafe_lookup_table::get_map() const
{
    std::vector<std::unique_lock<boost::shared_mutex> > locks;

    // ここで一気にロックを取得していてその順番が決定している
    for(unsigned i=0;i<buckets.size();++i)
    {
        locks.push_back(
            std::unique_lock<boost::shared_mutex>(buckets[i].mutex));
    }

    std::map<Key,Value> res;

    // データの内容を一気にコピーしている
    for(unsigned i=0;i<buckets.size();++i)
    {
        for(bucket_iterator it=buckets[i].data.begin();
            it!=buckets[i].data.end();
            ++it)
        {
            res.insert(*it);
        }
    }

    // デストラクタでロックが開放される
    return res;
}
```

listing6.11からのルックアップテーブルの実装は、それぞれのbucketを分割してlockかけたり、それぞれのbucketへreader concurrencyを利用するためのboost::shared_mutexを使用することによってルックアップテーブルのconcurrencyな機会を増加させます。

しかし、さらに細かいロックによってbucket上でのconcurrencyの潜在的可能性を増加させたらどうなるでしょうか?
次のセクションでは、イテレータをサポートしたスレッドセーフなlistコンテナを使うことによって、それを実施してみせます。

