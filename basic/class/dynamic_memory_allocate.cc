#include<iostream>
using namespace std;

class MyClass
{
	public:
		MyClass(char *str){
			cout << str << endl;
		}
};

class ArrayMyClass
{
	public:
		~ArrayMyClass(){
			cout << "ArrayMyClass desctructor START" << endl;
		}
};

int main()
{
	// 動的メモリの取得
	int *po;
	po = new int;                         // 型を指定してnewによる動的メモリ割り当て
	*po = 100;
	cout << *po << endl;
	delete po;

	// オブジェクトの割り当て
	MyClass *obj;
	obj = new MyClass("Start MyClass");   // newによるオブジェクトの動的メモリ割り当て
	delete obj;

	// 配列割り当て
	ArrayMyClass *aryobj;
	aryobj = new ArrayMyClass[5];         // 配列に対する動的メモリ割り当て
	delete [] aryobj;                     // 配列で割り当てたメモリを初期化する場合の方法

	return 0;
}
