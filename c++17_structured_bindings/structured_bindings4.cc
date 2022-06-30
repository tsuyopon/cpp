/*
 * ビルド方法:  g++ -std=c++1z structured_bindings4.cc 
 * 
 * 静的メンバ変数を持つクラスは、構造化束縛の宣言では無視される
 *
 * cf. https://cpprefjp.github.io/lang/cpp17/structured_bindings.html
 */
#include <iostream>
#include <utility>
#include <tuple>
#include <string>

struct X {
  int id = 3;
  std::string message = "Hello";
  double value = 3.14;

  // 静的メンバ変数や定数は、構造化束縛宣言では無視される(※1)
  static int static_value;
  static const int constant_value = 456;

  X()
  {
    static_value = 123;
  }

};
int X::static_value;

int main()
{

  // 構造体X中に(※1)で宣言した静的メンバ変数や定数は、構造化束縛宣言では無視されることになる
  auto [id, message, value] = X();

  std::cout << id << std::endl;        // 3
  std::cout << message << std::endl;   // Hello
  std::cout << value << std::endl;     // 3.14
}
