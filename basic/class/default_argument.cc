#include<iostream>
using namespace std;

/*
 *  デフォルト引数に関する使用方法について
 */

void MyClass( char *str = "hello"){    // デフォルト変数を利用している
	cout << str << endl;
}

void MyClass2(char *name="Azarashi", int age = 3){
	cout << "Name:" << name << "\tAge:" << age << endl;
}

int main(){
	MyClass();               // 引数を指定してないので、デフォルト引数が利用される
	MyClass("good evening"); // 引数を指定しているので、引数が利用される

	/* 注意
	 *   以下の例からわかるように、デフォルト引数は関数のオーバーロードで表現が曖昧になってしまうことがあります。
	 */
	MyClass2();              // 引数は指定せず、デフォルト引数を利用する
	MyClass2("Goma");        // 第1引数のみ指定する(但し、第２引数のみ指定することはできない)
	MyClass2("Goma", 5);     // 引数を指定し、デフォルト引数を利用しない

	return 0;
}
