#include<iostream>
#include<stdlib.h>
using namespace std;

/*
 * コピーコンストラクタの使用方法について(コピーコンストラクタの有用性確認)
 */

class MyClass {
		int *x;
	public:
		MyClass();
		MyClass(const MyClass &);
		~MyClass();
		void printX();
} myobj;

MyClass::MyClass(){
	x = (int *)malloc(5*sizeof(int));
	for(int i = 0; i < 5; i++){
		*(x+i) = i * 2;
	}
}

MyClass::MyClass(const MyClass &obj){
	x = (int *)malloc(5 * sizeof(int));
	for(int i = 0; i < 5; i++){
		*(x+i) = i;
	}
}

MyClass::~MyClass(){
	free(x);
}

void MyClass::printX(){
	for( int i=0; i < 5; i++){
		cout << *(x+i) << " ";
		cout << "\n";
	}
}

int main()
{
	MyClass obj = myobj;
	cout << "myobj START>" << endl;
	myobj.printX();

	cout << endl << "obj START>" << endl;
	obj.printX();
	return 0;
}
