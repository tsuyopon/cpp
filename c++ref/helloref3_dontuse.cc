/*
 * 参照とconst_castを組み合わせた誤用例
 */
#include<iostream>

void f(const int& x) {

  // xの参照のconst_castを外して、それをyの参照としている。つまり、yの値を書き換えることでxの値を書き換えてしまうことになる。
  int& y = const_cast<int&>(x); // xのconst属性を一時的に解除
  y = 42; // xを変更する

}

int main() {

  int a = 10;
  const int& b = a;
  f(b); // bのconst属性を一時的に解除し、aを変更する

  // 本来はbだけ値が変わりaの値が変わらないことを意図していたが、bはaの参照のために、f()側でconst_castで外してbの値を変更することでaにも波及するようになった。
  std::cout << a << std::endl; // 出力結果: 42
  return 0;
}
