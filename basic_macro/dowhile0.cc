//
// do ~ while(0)がどのように使われるのかのサンプル
//
// 参考URL
//   https://qiita.com/ymko/items/ae8e056a270558f7fbaf
// 

// [メリット]
// 1. マクロの誤った使い方を防ぐことができる。
//    1.1 マクロの定義の際に *MACRO などと先頭に*を付与して利用してしまった場合の悪影響をC++セマンティクスにより防ぐことができるようになる。
//    1.2 マクロの誤った使い方を防げる See: https://jp.quora.com/C-gengo-no-shitsumon-desu-do-while-0-no-riten-ha-nani-desu-ka
//    1.3 文法エラーを防ぐため
//      https://ryochack.hatenadiary.org/entry/20111022/1319252481
// 
// 2. do-whileを使った際に利用できるbreak文をつかって、そのスコープを即座に抜けることができるようになる。
//      https://qiita.com/ymko/items/ae8e056a270558f7fbaf
//      https://marycore.jp/coding/do-while-false-idiom/#break%E6%96%87%E3%81%A7%E5%87%A6%E7%90%86%E3%82%92%E6%89%93%E3%81%A1%E5%88%87%E3%82%8B%E3%81%93%E3%81%A8%E3%81%8C%E3%81%A7%E3%81%8D%E3%82%8B
// 2. 条件式が複雑になってしまった場合に簡潔に記述することができる。
//      https://marycore.jp/coding/do-while-false-idiom/#%E6%9C%AC%E3%82%A4%E3%83%87%E3%82%A3%E3%82%AA%E3%83%A0%E3%81%AE%E6%84%8F%E5%A4%96%E3%81%AA%E5%8A%B9%E6%9E%9C
// 3. マクロの末尾にセミコロンを必要にできる。
//      https://nitamago-archive.hatenablog.com/entry/20080626/1214493741
//
// [デメリット]
// なおデメリットとして考えられるのは以下だが、影響はほとんど無いらしい
// - バイナリサイズが少し増える
// - do-whileのオーバーヘッド



// TBD: あとでサンプルを記載する。
