// g++ sample6.cc -std=c++1y  (C++14以降でコンパイル可能)
// see https://cpprefjp.github.io/lang/cpp11/decltype.html

// template 型引数としての使用例
#include <iostream>
#include <utility>

template<typename T>
auto d(T&& x) {
  return x + x;
}

struct S {
  static constexpr int g = 20;
};

constexpr int S::g;

int main()
{
  auto l = [](auto&& x) {
    std::cout << "start\n";
    auto ret = d(std::forward<decltype(x)>(x));     // x の型のままで転送
    std::cout << "end\n";
    return ret;
  };
  std::cout << l(S::g) << '\n';   // 40
}
