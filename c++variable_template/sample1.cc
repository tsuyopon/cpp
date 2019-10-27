// C++11から追加された可変長テンプレートの仕組みについて
//
// 参考: https://docs.microsoft.com/en-us/cpp/cpp/ellipses-and-variadic-templates?redirectedfrom=MSDN&view=vs-2019
#include <iostream>

using namespace std;

void print() {
    cout << endl;
}

template <typename T> void print(const T& t) {
    cout << t << endl;
}

template <typename First, typename... Rest>                              // Restの方のみ"..."で定義されている。これにより可変長引数であることを示す。
void print(const First& first, const Rest&... rest) {                    // 第２引数の方に"... "が指定されている。
    cout << first << ", ";                                               // 最初の1つめの引数のみ出力する
    print(rest...); // recursive call using pack expansion syntax        // "rest..." により残りのも同様に出力する
}

int main()
{
    print();  // 1番目のoverloadであるprintが呼ばれる
    print(1); // 2番目のoverloadであるprintが呼ばれる

    // 3番目のoverloadであるprintが呼ばれる。ここで可変長のtemplateが呼ばれている。
    print(10, 20);
    print(100, 200, 300);
    print("first", 2, "third", 3.14159);
}
