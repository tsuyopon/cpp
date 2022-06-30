/*
 * std::string_viewを利用したサンプルです。
 * 
 * 通常はstd::string型でsubstrする際には動的にメモリ領域を確保して返却しており、対象文字列が大きいとメモリを大量に消費します。
 * std::string_viewは参照用に確保されたオブジェクトでありstd::stringから暗黙的にキャストされます。
 * std::string_viewのsubstrではメモリ領域を新たに確保することなく、アドレス操作によりこの問題を解決しています。
 *
 * see: https://www.educative.io/answers/what-is-the-cpp-string-view-in-cpp-17
 * cf. https://en.cppreference.com/w/cpp/string/basic_string_view
 */
#include <iostream>
using namespace std;

int main() {
  std::string str = "The quick brown fox jumps over the lazy dog. And then runs away!!!";

  //'string::substr' returns a new string
  //this function is memory-intensive, specially if the string is realy long
  std::cout << str.substr(5, 15) << '\n';

  //The creation of string_view from the literals does not 
  //require a dynamic allocation.
  std::string_view sv = str;  // std::stringから暗黙的にstd::string_viewにキャストされる

  // string_view::substr returns a new string_view. No new memory allocated
  std::cout << sv.substr(5, 15) << '\n';
}
