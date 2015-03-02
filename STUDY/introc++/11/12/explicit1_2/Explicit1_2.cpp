/*
 * 呼び出しているプログラムは6.10節のプログラムをコピーしたものです。
 */

//Copy1.cpp
#include "IntArray.h"
#include <iostream>
using namespace std;

void Show(const IntArray& array) {
	cout << array.Size() << endl;
}

int main()
{
	// コンストラクタ定義にexplicitが付与されているので、以下は明示的にキャストをしない限りはコンパイルエラーとなる。
	// 暗黙のキャストは思わぬバグを引き起こす可能性があるために、引数が1つになる可能性のあるコンストラクタがあれば、
	// コピーコンストラクタをのぞいてはexplicitを付与しておくのが無難です。
//	Show(5);

	IntArray array(5);
	Show(array);
}

