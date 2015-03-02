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
	// これは "Show(IntArray(5))"というテンポラリオブジェクトの作成が行われる形に暗黙的にキャストされます。
	// IntArray(5)は配列を表す型であるのに対して、5という値はただの１つの数値を表す型にすぎません。
	// これらの間の自動的な変換は行われるべきではありません。
	// このような場合にはメソッド定義にて「explicit IntArray(int size);」の様にexplicitを付与して、暗黙的キャストを
	// 禁止するようにします。(このサンプルはexplicit1_2のプログラムにてのせています。)
	Show(5);
}

