#include <iostream>
using namespace std;

int main(){
	typedef const int* IntCPtr;   //int型へのポインタ型の同義語IntPtrを定義する。constを付与

	int n = 0;
	int m = -1;

	IntCPtr p = &n;     // const int* p = &n
	IntCPtr q = &n;     // const int* q = &n

	// pやqのアドレスを変更することは可能です。
	// つまり、const int*は、アドレスを変更して値を変更することは問題無いようです。
	p = &m;
	q = &m;
	cout << "*p = " << *p << endl;
	cout << "*q = " << *q << endl;

	// ただし、pやqの値自体を変更しようとするとコンパイルエラーとなります。 以下の行をコメントインして試してみて下さい。
//	*p = 1;
//	*q = 2;
//	cout << "*p = " << *p << endl;
//	cout << "*q = " << *q << endl;

}
