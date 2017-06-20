#include<iostream>

/*
 * 最も危険なキャストです。他のキャストが利用できない場合の最終手段と思ってください。
 *
 * このキャストは強制的にビット構成を変更するので、 void*の変換や整数型のポインタへの変換などに使用します。 
 * このキャストは危険なので、使う気をなくすような長い名前が付けられています。 
 * reinterpret_castはビット構成を再解釈するだけなので、 constやvolatileの除去は出来ませんし、 継承関係にあってもポインタは再計算されません。
 */
int main(void) {

    // 整数値をアドレスとみなしてポインタ変数に向ける
    int i = 123456;
    int* p = reinterpret_cast<int*>( i );

    long hoge = 1111;
    int* hogehoge = reinterpret_cast<int*>(hoge);
}
