// 型を自動的に判定する関数を定義する
#include <iostream>
#include <typeinfo>

// 型を適切に判断してaddした結果を返す
template<typename T, typename U>
auto add(const T& lhs, const U& rhs)
  -> decltype(lhs + rhs)                // add の戻り値型は lhs + rhs の式の型
{
  return lhs + rhs;
}

int main()
{
  auto a = add(1, 2.0F);                // Fはfloat
  auto b = add(1, 2.0L);                // Lはlong double
  auto c = add(1, 30.0E3);              // Eの後の数値は10の何乗かを表す
  auto d = add(01, 056);                // 8進数
  auto e = add(0x1, 0x2);               // 16進数
  auto f = add(1, 100U);                // Uはunsigned
  auto g = add(1, 50000L);              // Lはlong
  auto h = add(1, 50000UL);             // ULはunsigned long

  std::cout << std::fixed << a << std::endl;
  std::cout << std::fixed << b << std::endl;
  std::cout << std::fixed << c << std::endl;
  std::cout << std::fixed << d << std::endl;
  std::cout << std::fixed << e << std::endl;
  std::cout << std::fixed << f << std::endl;
  std::cout << std::fixed << g << std::endl;
  std::cout << std::fixed << h << std::endl;

  std::cout << "a type: " << typeid(a).name() << std::endl;
  std::cout << "b type: " << typeid(b).name() << std::endl;
  std::cout << "c type: " << typeid(c).name() << std::endl;
  std::cout << "d type: " << typeid(d).name() << std::endl;
  std::cout << "e type: " << typeid(e).name() << std::endl;
  std::cout << "f type: " << typeid(f).name() << std::endl;
  std::cout << "g type: " << typeid(g).name() << std::endl;
  std::cout << "h type: " << typeid(h).name() << std::endl;
}
