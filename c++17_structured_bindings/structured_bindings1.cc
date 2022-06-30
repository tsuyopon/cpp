/*
 * ビルド方法:  g++ -std=c++1z structured_bindings1.cc
 *
 * 構造化束縛(structured bindings)は、組やタプル、配列や構造体を分解して各要素を取り出す機能です。
 * このプログラムは構造化束縛を使った最も単純なサンプルとなっています。
 *
 * cf. https://cpprefjp.github.io/lang/cpp17/structured_bindings.html
 */
#include<iostream>
#include<string>

using namespace std;

std::pair<int, std::string> f()
{
  return {3, "Hello"};
}

int main(){

	// 関数f()の戻り値である整数と文字列の組を分解する。
	// pairのfirstをid変数に代入し、secondをmessage変数に代入する。
	// id変数の型はfirstの型(int)となり、message変数の型はsecondの型(string)となる。
	auto [id, message] = f();

	std::cout << id << std::endl;      // 「3」が出力される
	std::cout << message << std::endl; // 「Hello」が出力される
}
