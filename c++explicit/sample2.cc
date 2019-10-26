// C++11では、explicitを付けたコンストラクタは、X x = {a, b, c};のような代入演算子を伴うリスト初期化が禁止されます。
// 例として、string(int pos, int len)みたいなコンストラクタは、explicitにしたほうが可読性があって良い
//
// このプログラムはexplicitを外さないとコンパイルできません。
//
// 参考: https://faithandbrave.hateblo.jp/entry/2018/03/19/163816
struct X {
    X(int, int) {}
};

struct Y {
    explicit Y(int, int) {}    /* explicitを外せばコンパイルが通ります */
};

int main() {
    X x {1, 2}; // OK
    Y y {1, 2}; // OK

    X x2 = {1, 2}; // OK
    Y y2 = {1, 2}; // error: converting to 'Y' from initializer list would use explicit constructor 'Y::Y(int, int)'
}
