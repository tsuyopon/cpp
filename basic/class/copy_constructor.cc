#include<iostream>
using namespace std;

/*
 * コピーコンストラクタの使用方法について
 */

class MyClass {
	public:
		char *str;

		// 通常のコンストラクタ指定
		MyClass(){
			str = "first";
		}

		// コピーコンストラクタが定義(オブジェクトのコピーがとられた際に実行される処理)
		MyClass(const MyClass &myobj){
			str = "second";
		}
} myobj;

int main()
{
	MyClass obj = myobj;         // オブジェクトのコピー(コピーコンストラクタが呼び出されます)
	cout << myobj.str << endl;
	cout << obj.str << endl;
	return 0;
}
