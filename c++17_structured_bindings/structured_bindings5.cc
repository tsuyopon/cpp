/*
 * ビルド方法:  g++ -std=c++1z structured_bindings5.cc 
 * 
 * mapを範囲for文で走査する
 *
 * cf. https://cpprefjp.github.io/lang/cpp17/structured_bindings.html
 */

#include <iostream>
#include <map>
#include <string>

int main()
{
  std::map<std::string, int> m = {
    {"Alice", 3},
    {"Bob", 1},
    {"Carol", 4}
  };

  // mapの各要素をキーと値に分解する。
  // const auto&ではなくauto&にした場合は、const std::string&型のkey変数と、int&型のvalue変数に分解される。
  for (const auto& [key, value] : m) {
    std::cout << key << " : " << value << std::endl;
  }
}
