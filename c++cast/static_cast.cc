#include <iostream>

/*
 * 最初に試してみるべきキャストです。ポインタに関して厳しいだけの普通のキャストです。
 * static_castは静的なキャストで、名前の通りコンパイル時にエラーチェックが行われ、 実行時にはすでに変換後の型は決定しています。
 *
 *    この型変換の時、実行時に自動的に安全性を確認することはありません。例えば int の値を char に代入するときに桁あふれするかどうかとか、ダウンキャ>ストの時にそれは安全なのかとかです。
 *    ただ、実行しなくても危険な変換だと分かるときはコンパイルエラーになります。例えば、ポインタから int への変換、int からポインタへの変換、int へ>のポインタから double へのポインタへの変換、全く関係ないクラスへのポインタ同士の型変換などがそうです。 
*/
class Base {};
class Derived: public Base {};

int main(void) {

    // NOTE: intからshortやdoubleからshortなどの変換も情報落ちなどを気にせずコンパイルエラーとなることはありません。
    // intからの変換
    int myint = 10;
    int fromint1          = static_cast<int>(myint);
    unsigned int fromint2 = static_cast<unsigned int>(myint);
    signed int fromint3   = static_cast<signed int>(myint);
    double fromint4       = static_cast<double>(myint);      
    float fromint5        = static_cast<float>(myint);      
    long  fromint6        = static_cast<long>(myint);      
    short fromint7        = static_cast<short>(myint);      
    char fromint8         = static_cast<char>(myint);      
    uint8_t fromint9      = static_cast<uint8_t>(myint);
    uint32_t fromint10    = static_cast<uint32_t>(myint);
    //int* fromint20      = static_cast<int*>(myint);         // NOTE: 通常の型からポインタ型に変換するキャストはコンパイルエラーになる

    // doubleからの変換
    double mydouble = 2.25;
    short fromdouble1  = static_cast<short>(mydouble);
    float foomdouble2  = static_cast<float>(mydouble);
    double fromdouble3 = static_cast<double>(mydouble);

    // void*からの取り出し
    int* testvoid = new int(9);
    void* testvoidp = testvoid;
    float* testvoidf = static_cast<float*>(testvoidp);

    // NOTE: upcastやdowncastで利用することができる。(See http://www.cplusplus.com/doc/tutorial/typecasting/)

    // downcastの場合
    Base * a = new Base;
    Derived * b = static_cast<Derived*>(a);

    // upcast
    Derived * a2 = new Derived;
    Base * b2 = static_cast<Base*>(a2);
}
