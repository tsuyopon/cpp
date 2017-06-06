// 変換演算子の型としての使用例
#include <iostream>

struct S {
  int i;
  S(int i) : i(i) {}
  operator decltype(i)() { return i; }        // int 型への変換演算子  つまり operator int(){ return i; }と同じ
};

int main()
{
  S s(42);
  std::cout << s << '\n';
}
