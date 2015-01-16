#include<iostream>
using namespace std;

/*
 *  関数にアドレスを渡す作業をブラックボックス化する
 *  関数の参照を返却する
 */
class MyClass {
	private:
		int Num;
	public:
		char *str;
		int & getNum();                      // これで参照を返却します
};

int & MyClass::getNum(){                     // 参照を返す関数です。
	return Num;
}

void setString(MyClass &obj, char *str){     // &の指定
	obj.str = str;
}

int main()
{
	/*
	 * C言語では、関数に直接アドレスを渡しますが、
	 * C++では関数にアドレスを渡すという作業をブラックボックス化できます。
	*/
	MyClass obj;
	setString(obj, "helloworld");    // アドレスを引き渡しているわけでないことに注意
	cout << obj.str << endl;

	/*
	 * setterとgetter双方の役割をする関数を作成することが出来ます。
	 */
	obj.getNum() = 100;
	cout << obj.getNum() << endl;

	return 0;
}
