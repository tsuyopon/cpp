/*
 * 純粋仮想関数のサンプルです。
 * これは、派生クラスを呼び出すために基底クラスでSetBase()という無駄な関数を無理矢理定義していました。
 * しかし、ヘッダファイルに「virtual void SetBase() = 0」と記述するだけで実体を作成する必要がありません。
 */
#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){
	InputStream istream;
	cout << "> " << flush;
	istream.Set();
	cout << istream.Get() << endl;
}
