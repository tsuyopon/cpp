#include<iostream>
using namespace std;

class Base {
	public:
		char *str;
		void print(){
			cout << "Base Class" << endl;
		}
};

class Derived : public Base {
	public:
		int i;
		void print(){
			cout << "Derived Class Extends Base Class" << endl;
		}
} obj;

void getRef(Base &obj){
	cout << obj.str << ": getRef()" << endl;
}

int main()
{
	obj.str = "hello";
	Base *po = &obj;              // クラス型ポインタに対して派生クラスのアドレスを代入できます
	obj.print();                  // Derivedクラスのprint()が呼び出されます
	po->print();                  // Baseクラスのprint()が呼び出されます
	cout << po->str << endl;
	getRef(obj);                  // getRefの引数としては、Baseクラスだが、ここでは派生クラスのオブジェクトが指定されていることに注意
	return 0;
}
