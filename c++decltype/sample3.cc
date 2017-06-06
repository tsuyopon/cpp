// ネストした名前の指定子としての使用例する場合
#include <iostream>
#include <typeinfo>

struct S {
  int i = 42;
  float j = 30.0;
};

int main()
{
  S s;
  auto mp = &decltype(s)::i;             // mp の型は int S::* 型（S の int 型のメンバへのポインタ）
  auto mp2 = &decltype(s)::j;             // mp の型は int S::* 型（S の int 型のメンバへのポインタ）
  std::cout << s.*mp << std::endl;
  std::cout << s.i << std::endl;

  std::cout << s.*mp2 << std::endl;
  std::cout << s.j << std::endl;

  // mp
  std::cout << "typeid: " << typeid(mp).name() << std::endl;
  std::cout << "typeid: " << typeid(s.i).name() << std::endl;
  std::cout << "typeid: " << typeid(s.*mp).name() << std::endl;

  // mp2
  std::cout << "typeid: " << typeid(mp2).name() << std::endl;
  std::cout << "typeid: " << typeid(s.j).name() << std::endl;
  std::cout << "typeid: " << typeid(s.*mp2).name() << std::endl;
}
