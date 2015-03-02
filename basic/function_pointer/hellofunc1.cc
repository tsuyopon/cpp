#include<iostream>
using namespace std;

/*
 *  オーバーロードされた関数ポインタ使用方法について
 */

void MyMethod(){
	cout << "hello" << endl;
}
void MyMethod(char *str){
	cout << str << endl;
}

int main()
{
	void (*po1)(), (*po2)(char *);   // オーバーロードされた関数ポインタの宣言方法

	po1 = MyMethod;
	po2 = MyMethod;

	(*po1)();
	(*po2)("good evening");

	return 0;
}
