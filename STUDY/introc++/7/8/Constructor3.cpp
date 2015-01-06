/*
 * 今回のケースでは、基底クラスのコンストラクタでは引数を必ず持ちます。
 * この場合には、派生クラスが呼ばれた際にそのコンストラクタにて、基底クラスのコンストラクタに対する引数を指定してあげなければなりません。
 */
#include "InputStream.h"
#include <iostream>
using namespace std;

int main(){
	InputStream stream(3);
	cout << stream.Get() << endl;
}
