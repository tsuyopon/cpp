#include<iostream>
using namespace std;

/*
 *  クラス定義・オブジェクト定義方法
 *  メンバー関数定義方法
 *  private取得方法
 */

class MyClass{
	// ここに定義されるデータのことをメンバーと呼びます。
	private:
		char *test;
	public:
		char *str;
		void print(){
			cout << str << endl;
		}
		void setPrivate(char *set){       // testはprivateで直接操作できないのでpublic関数から操作します
			test = set;
		}
		void getPrivate(){            
			cout << test << endl;
		}
} obj;

int main()
{
	obj.str = "helloworld";
	obj.print();
	obj.setPrivate("konnitiha");
	obj.getPrivate();
}
