/*
 * プログラムのコンパイルができますが、実行時にエラーがでます
 * これを対処したプログラムがsample2にあります。
 */
#include "IntArray.h"
#include <iostream>
using namespace std;

int main(){
	IntArray a(5);
	IntArray b(5);

	cout << "we must input integer 5 times." << endl;
	for( int i = 0, size = a.Size(); i < size; i++){
		int n;
		cin >> n;
		a.Set(i, n);
	}

	cout << "copy obj. and set double value into copied obj." << endl;
	b = a;
	for( int i = 0, size = b.Size(); i < size; i++){
		b.Set(i, b.Get(i) * 2);
	}

	cout << "Output both object" << endl;
	for(int i = 0, size = a.Size(); i < size; i++){
		cout << a.Get(i) << " -> " << b.Get(i) << endl;
	}

	cout << "End of main()";
}
