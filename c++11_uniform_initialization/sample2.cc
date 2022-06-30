/*
 * 一様初期化を用いた配列メンバ変数の初期化
 */
#include <iostream>
#include <vector>

struct X {
    int ar[3];

    // 波カッコによる初期化は、メンバ変数の配列をコンストラクタで初期化するために使用することもできます。これはC++03ではできませんでした。
    X() : ar{1, 2, 3} {} // 配列メンバ変数を初期化
};

int main()
{
    X x;

    for (int a : x.ar) {
        std::cout << a << std::endl;
    }
}
