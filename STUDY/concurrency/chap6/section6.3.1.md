6.3 Designing more complex lock-based data structures

スタックやキューはシンプルです。
つまり、IFは極めて制限されていて、それらは特定の目的に対してしっかりとフォーカスされています。
すべてのデータ構造がシンプルというわけではありません。ほとんどのデータ構造は様々な操作を可能にしています。原則として、これらはconcurrencyへの大きな機械を与えています。
しかし、その機会は複数でのアクセスパターンが考慮に含まれるために、データを保護するタスクをより困難にします。 (英文構造確認)
振舞われる様々な操作の性格な性質というものはconcurrencyなアクセスのデータ構造を設計するときに重要となります。

6.3.1 Writing a thread-safe lookup table using locks

A lookup table or dictionary associates values of one type (the key type) with values of either the same or a different type (the mapped type).


一般的にはそのようなデータ構造の裏にある意図としては、与えられたキーに漢連付けられたデータを要求するコードを許すことである。
C++標準ライブラリではこの機能はstd::map<>, std::multimap<>, std::unordered_map<>,　std::unordered_multimap<> のようなコンテナで提供されています。
ルックアップテーブルはstackやqueueよりも使用パターンがことなります。
stackやqueue上のほとんどすべての操作は要素を追加するか・要素を削除するかという修正が行われる一方で、lookup tableというのは滅多に修正が発生しません。

listing3.13の単純なDNS Cacheはそのようなシナリオ例の１つです。std::map<>と比べてはるかに削減されたI/Fが特徴となっている。

stackやqueueで見られるように、データ構造は複数スレッドでconcurrentにアクセスされることになっているときに標準コンテナのInterfaceは適切ではない。
なぜなら、インターフェース設計においては固有のレースコンディション状態あるので、それらを取り除かなければならない。

concurrencyからみたstd::maps<>インタフェースが持つ最も大きな問題というのは、イテレーションである。

他のスレッドがコンテナへアクセスしたり修正したりする際に、コンテナへの安全なアクセスを提供するというイテレータを持つことは可能であるけれども、これはトリッキーな命題である。

正しくイテレータを扱うことは、イテレータが参照していると要素の削除をしている他のスレッドのような問題を扱わなければならないということ意味します。(XXX)

スレッドセーフなlookup table I/Fを最初にカットするために、イテレータをスキップできるでしょう。(XXX)


std::map(や他の標準ライブラリの連想コンテナ)のインターフェースがイテレータによって大部分がベースとなっていることを考慮すると、それらのコンテナは別においておいて、地盤から設計することを選択する方が価値があるだろう。

テーブルをルックアップする際にわずかな操作があります。
- 新しいkey/valueを追加する
- 与えられたkeyに対するvalueを変更する
- key/valueを削除する
- 必要あれば、与えられたkeyに対する値を取得する。

コンテナには操作にはまだ役にたつものがあります。コンテナが空かどうかのチェックや、keyリストの完全なスナップショットの提供、key/valueペアの完全なスナップショットの提供などです。



もし、あなたが参照は返さない、各メンバー関数の全体にmutex lockを配置したりするなどシンプルなスレッドセーフガイドラインに従うのであれば、これらはすべて安全です。

レースコンディションへの最大限の可能性というのは、key/valueペアが追加されるときです。
もし、２つのスレッドが新しいvalueを追加した場合、最初の１つだけが可能で、２番目は失敗するでしょう。

１つの可能性は、listing3.13のDNS cacheでみられたように追加と変更を１つのメンバー関数に含めることです。(XXXX)


interfaceの観点からのその他の興味深い点としては、
１つのオプションは、keyが存在しなかった場合のケースとしての戻り値としてユーザーに"default"値を提供することです。

mapped_type get_value(key_type const& key, mapped_type default_value);

もしdefault_valueが明示的に与えられなかったら、このケースではデフォルトコンストラクタとして生成されたインスタンスのmapped_typeが使われる。




これは単純にmapped_typeのインスタンスの代わりにstd::pair<mapped_type, bool>を返却する拡張であろう。boolはvalueが存在しているかどうかを示しています。
他のオプションとしては、値を参照するスマートポインタを返却することです。
もしポインタの値がNULLであれば、戻すべき値が存在しないということを意味しています。


すでに述べたように、一度interfaceが決定してしまったら、スレッド安全はデータ構造に基づいて保護するためにすべてのメンバー関数の周りに1つのmutexや単純なロックによって保証されていると思います。

しかしながら、これはデータ構造の読み込みや修正のための関数の分割によって提供されるconcurrencyの可能性を無駄遣いしていることになりうる。

１つのオプションはlisting3.13に記載されたboost::shared_mutexのように複数のreader threadsをサポートした、１つのwriter threadをサポートしているmutexを使うことです。


これはconcurrencyなアクセスを改善する可能性があるだろうが、1つのスレッドだけが1度にデータ構造を修正することができる。




DESIGNING A MAP DATA STRUCTURE FOR FINE-GRAINED LOCKING


section6.2.3で議論されたqueueと同様に、細かいロックを許可するためにあなたはstd::map<>のような既存コンテナをただラッピングするのではなく、データ構造の詳細を注意深く確認する必要があります。


次の様にlookup tableのような連想コンテナを実装するには３つの共通した方法があります。
- バイナリツリー, such as red-black tree
- 配列
- ハッシュテーブル


バイナリツリーはconcurrencyのための拡張機会を十分には提供してくれません。
すべてのlookupや修正はroot nodeから開始することによってアクセスしなければならない。root nodeもそれゆえにlockが必要となります。
このlockはスレッドがnodeを下へといどうしていく際に解放されるが、全データ構造に対するシングルロックよりも良くない。

配列はさらに悪くなります。なぜなら、与えられたデータが配列中のどこに格納されるのか前もってわからないからです。それゆえに、全配列に対してシングルロックが必要となってきます。


最後にハッシュテーブルです。
bucket(入れ物)における固定値だと仮定されるので、keyはそのkeyに純粋に結びつけられています。(ちょっと英訳が..)
これはbucketごとに安全な分割されたロックを持つことができることを意味します。
もし、multiple readerやsingle writerをサポートしているというmutexを再度使った場合、N-foldであるconcurrency(Nはbucket数)の機会を増加させることができます。
欠点としてはkeyに対する良いハッシュ関数を利用する必要があるということです。
C++標準ライブラリはstd::hash<>テンプレートを提供しています。このテンプレートは良いハッシュ関数を利用する目的として利用することができます。



そしてユーザーは簡単に他のkey typeへと特化させることができます。

もし、標準の整列されていないコンテナ(unorderd containers)を利用したり、関数オブジェクトのtypeを受け取るのであれば、ユーザーはそれらのkey typeのために特化したstd::hash<>、ハッシュ関数の分割を提供するかどうかを選択することができます。



If you follow the lead of the standard unordered containers and take the type of the function object to use for doing the hashing as a template parameter, the user can choose whether to specialize std::hash<> for their key type or provide a separate hash function.


じゃあ、いくつかのコードを見てみましょう。
スレッドセーフなlookup tableの実装はどうなっているのか? 1つの可能性としていかに記載されています。

