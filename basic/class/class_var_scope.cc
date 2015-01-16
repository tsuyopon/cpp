#include <iostream>
using namespace std;

/*
 * 各種変数のスコープ(1)〜(4)の有効範囲
 * 関数のスコープ(A)〜(B)の有効範囲
 * 「::」グローバルスコープ解決演算子
 *
 */

char *str = "Azarashi";                    // (1)

void function(){                           // (A)
	cout << "function()" << endl;
}

/*
 * MyClass Start
 */
class MyClass {
	public:
		char *str;                         // (2)
		void print(char *);
		void function();
};

void MyClass::print(char *str){            // (3)
	cout << str << endl;                   // (3)のstrを出力させる
	cout << MyClass::str << endl;          // (2)のstrを出力させる
	cout << ::str << endl;                 // (1)のstrを出力させる(グローバルスコープ解決演算子「::」)
}

void MyClass::function(){                  // (B)
	cout << "MyClass::function()" << endl; // (B)自身を出力
	::function();                          // (A)を出力
}

/*
 * main() Start
 */
int main()
{
	char *str = "Ashika";                  // (4)

	cout << "##### MyClass str output" << endl;
	MyClass obj;
	obj.str = "Dolphin";
	obj.print("WHALE");

	cout << "##### main str output" << endl;
	cout << "local str:"  << str << endl;  // (4)のstrを出力させる
	cout << "global str:" << ::str<< endl; // (1)のstrを出力させる

	cout << "##### function output" << endl;
	obj.function();


	return 0;
}

