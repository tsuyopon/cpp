#include<iostream>

using namespace std;

class CTest
{
	int a[100];
public:
	CTest* RetThis(){ this->hoge(); return this; }  // thisを使うことによって内部関数を呼び出す
	void hoge(){ cout << "hogehoge" << endl;}
};

int main(){
	CTest test1, test2;
	cout << "test1 : " << &test1 << endl
		 << "test2 : " << &test2 << endl
		 << "test1 : " << test1.RetThis() << endl
		 << "test2 : " << test2.RetThis() << endl;
	return 0;
}
