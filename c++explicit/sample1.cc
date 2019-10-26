// explicitキーワードは引数を一個しか持たないコンストラクタの暗黙の変換を禁止します。
// つまり、explicitを付けて宣言しておくと、そのコンストラクタは明示的な呼び出ししかできなくなる。
//
// このプログラムはexplicitを外さないとコンパイルできません。
// 
// 参考URL
//    http://exlight.net/devel/cpp/explicit.html
#include<iostream>

class Hoge {
    int hoge;
public:
    /*  コンパイルしようとすると以下のエラーが表示されます。
     *  error: conversion from 'int' to non-scalar type 'Hoge' requested‘
     */
    explicit Hoge(int hoge) { this->hoge = hoge; }  // このexplicitを外すとmainでコンパイルが通ります
    int getHoge(void) { return hoge; }
};

int main(void) {
    // “C obj = 10;”explicitが指定されていない場合には“C obj(10);”に変換される（等価である）．
    Hoge hoge = 10;         // 暗黙的呼び出し         *** この場合はエラーとなる***
    Hoge hoge2(20);         // 明示的呼び出し
    return hoge2.getHoge();
}
