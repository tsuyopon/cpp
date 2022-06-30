/*
 * ビルド方法:  g++ -std=c++1z structured_bindings3.cc 
 * 
 * 配列を分解する
 *
 * cf. https://cpprefjp.github.io/lang/cpp17/structured_bindings.html
 */
#include <iostream>

int main()
{
  {
    int ar[] = {3, 1, 4};

    // 配列を分解する。
    // ar[0]がaに代入され、
    // ar[1]がbに代入され、
    // ar[2]がcに代入される。
    // 分解する要素数は、配列の要素数と同じであること
    auto [a, b, c] = ar;

    std::cout << a << std::endl;  // 3 
    std::cout << b << std::endl;  // 1
    std::cout << c << std::endl;  // 4
  }
  std::cout << std::endl;


  // 参照の例
  {
    int ar[] = {3, 1, 4};
    auto& [a, b, c] = ar;

    // ar[1]を値2に書き換える
    b = 2;

    std::cout << ar[0] << std::endl;  // 3
    std::cout << ar[1] << std::endl;  // 2
    std::cout << ar[2] << std::endl;  // 4
  }
}

