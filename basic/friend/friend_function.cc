#include<iostream>
using namespace std;

/*
 * フレンド関数の使用法について
 */

class MyClass {
		char *str;

		/* フレンド関数を定義しています
		 *   ・フレンド関数はメンバー関数ではない
		 *   ・thisポインターも存在しない
		 *   ・継承もされません
		 */
		friend char *getStr(MyClass &);
	public:
		MyClass(char *str){
			MyClass::str = str;
		}
} obj("hello");

char *getStr(MyClass &obj){
	return obj.str;                   // MyClassの非公開(private)メンバーにアクセスしています。
}

int main()
{
	cout << getStr(obj) << endl;      // obj.getStr()という呼び出し方はできないので注意が必要です!
	return 0;
}
