#include<iostream>
using namespace std;

/*
 * オブジェクトを渡す関数の作成方法
 * オブジェクトを返す関数の作成方法
 */

class MyClass {
	public:
		char *str;
		~MyClass();
} obj;

MyClass::~MyClass(){
	cout << str << endl;
}

MyClass getMyClassObject(char *str){                     // MyClassオブジェクトを返却するメソッド
	MyClass obj;
	obj.str = str;
	return obj;
}

void func(MyClass *obj){                                 // MyClassオブジェクトを引数として取得するメソッド
	obj->str = "My Name Is Second";
}

int main()
{

	// クラスメソッドからオブジェクトを取得する
	MyClass obj2 = getMyClassObject("My Name Is Third");
	cout << obj2.str << endl;

	// クラスメソッドにオブジェクトを引き渡す
	obj.str = "My Name Is First";
	func(&obj);

	return 0;
}
