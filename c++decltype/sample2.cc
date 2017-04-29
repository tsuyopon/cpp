// 変数宣言から型を自動的に判断する
#include <iostream>
#include <typeinfo>

int main()
{
  int i = 10;
  decltype(i) j = i;                    // j は int 型
  decltype((i)) k = i;                  // k は int& 型（i は lvalue で丸括弧が付いているので）
  decltype(i)* p = &i;                  // i は int*型

  i = 42;
  std::cout << j << ", " << k << ", " << *p << ", " << p << std::endl;
  std::cout << typeid(i).name() << std::endl;
  std::cout << typeid(j).name() << std::endl;
  std::cout << typeid(k).name() << std::endl;  // 参照だが出力内容に違いは無い模様
  std::cout << typeid(p).name() << std::endl;  // Piとなる
}

