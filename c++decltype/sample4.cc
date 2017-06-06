// new 式の型、キャスト、および、明示的デストラクタ呼び出しの一部としての使用例
#include <iostream>

struct S {
  S() { std::cout << "S()\n"; }
  ~S() { std::cout << "~S()\n"; }
};

S f();

int main()
{
  std::cout << "allocate\n";
  void* p = ::operator new(sizeof(f()));

  std::cout << "construct\n";
  ::new(p) decltype(f());                       // 配置 new で p の指すメモリに S 型のオブジェクトを構築

  std::cout << "destruct\n";
  auto sp = static_cast<decltype(f())*>(p);     // デストラクタ呼び出しのため、S 型へのポインタにキャスト
//  sp->~decltype(f())();                         // 明示的デストラクタ呼び出しで sp の指すメモリの S 型オブジェクトを破棄

  std::cout << "deallocate\n";
  ::operator delete(p);
}
