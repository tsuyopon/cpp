#include <iostream>

/*
 * 
 * static_castは静的なキャストで、名前の通りコンパイル時にエラーチェックが行われ、 実行時にはすでに変換後の型は決定しています。
 * int型からdouble型や、 double型からfloat型といった、 一般的なキャストに使用します。
 * 具体的には、暗黙的な変換が存在する場合にコンパイルが成功し、 キャストが不正な(キャストできない)場合はコンパイルエラーとなります。 
 *
 */
int main(void) {
    int hoge = 10;
    double piyo = 2.25;

    int piyopiyo = static_cast<int>(piyo);
    double hogehoge = static_cast<double>(hoge);
}
