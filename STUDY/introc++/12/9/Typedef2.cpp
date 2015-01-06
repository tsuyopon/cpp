#include <iostream>
using namespace std;

int main(){
	typedef int* IntPtr;   //int型へのポインタ型の同義語IntPtrを定義する。

	int n = 0;

	// "const char*"と"char const*"の意味がかわらないように、
	// "const IntPtr"と"IntPtr const"の意味もかわりません。
	const IntPtr p = &n;     // const int* p = &n
	IntPtr const q = &n;     // int* const q = &n

	// 以下の２行をコメントインするとコンパイルエラーとなります。
//	p = &n;
//	q = &n;

	*p = 1;
	cout << "*p = " << *p << endl;
	cout << "*q = " << *q << endl;

	*q = 2;
	cout << "*p = " << *p << endl;
	cout << "*q = " << *q << endl;

}
