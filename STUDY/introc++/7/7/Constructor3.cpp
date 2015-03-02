/*
 * コンストラクタは基底クラスが呼ばれた後に派生クラスを呼び出します。
 * デストラクタは派生クラスが呼ばれた後に、基底クラスが呼ばれます。
 */
#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){
	InputStream stream;
	cout << stream.Get() << endl;
}
