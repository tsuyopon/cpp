/*
 * ビルド方法:  g++ -std=c++1z structured_bindings6.cc 
 * 
 * map::insert()の戻り値を分解する
 *
 * cf. https://cpprefjp.github.io/lang/cpp17/structured_bindings.html
 */
#include <iostream>
#include <map>
#include <string>

int main()
{
  std::map<std::string, int> m;

  // 単一要素をとるmap::insert()メンバ関数は、戻り値としてpair<iterator, bool>を返す。
  // firstは指定したキーを保持する要素へのイテレータ、secondは挿入に成功したかを表すbool値。
  m.insert({"Alice", 3});
  auto [it, inserted] = m.insert({"Alice", 1}); // キーがすでに登録されていたら挿入に失敗する

  std::cout << it->first << std::endl;                   // Alice
  std::cout << it->second << std::endl;                  // 3
  std::cout << std::boolalpha << inserted << std::endl;  // false
}
