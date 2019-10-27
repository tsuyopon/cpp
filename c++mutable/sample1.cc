/*
 * mutableありとmutableなしの違いを確認するプログラムです。
 * constメンバ関数によってメンバ変数が変更されないということを保証しますが、mutableを付与するとconstの干渉を受けなくなります。
 *
 * ISMUTABLE定義変数を指定した場合にはコンパイルできますが、指定しないとコンパイルエラーになります。
 * $ g++ -DISMUTABLE sample1.cc
 *
 * 参考: https://blog.kcg.ne.jp/naginagi/2013/11/18/mutable%E3%81%AB%E3%81%A4%E3%81%84%E3%81%A6/
 */

#include<iostream>


// mutableの使い方としては、クラス内のメンバ関数から操作したい
class CLASS{
public:
#ifdef ISMUTABLE
        mutable int value_;                      // constで定義されたクラスの値を変更するためにはmutableが必要である
#else
        int value_;
#endif // ISMUTABLE
        int value2_;
        CLASS(){ value_ = 0; }                   // mutableでなかろうが、mutableであろうが、コンストラクタの中で値を変更するのはコンパイルエラーにならず問題無い
        void init() const { value_ = 0; }        // コンストラクタ以外のメンバ関数内でmutableでない変数を初期化するとコンパイルエラーとなる
};


// 前提としては、CLASSがconst宣言されている場合であることに注意してください。
int main()
{
        const CLASS c;                          // constでクラス定義がされている場合、(重要)
        c.value_ = 10;                          // publicメンバ変数でもmutable定義されていれば書き換え可能
//        c.value2_ = 20;                       // この場合にはmutable定義されていないので、必ずコンパイルエラーとなる。
}
