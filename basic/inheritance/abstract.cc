#include<iostream>
using namespace std;

/*
 *  抽象クラスについて
 */

// 抽象クラスは、実体が無いのでオブジェクトを作ることができません。
class Parent {
	pubilc:
		// 「=0」と代入しているのは定義が無いことを表していて、これがC++での抽象メソッドの定義です。
		virtual void print() = 0;               
};

class Child1 : public Parent {
	public:
		void print(){                              // Parentクラスを継承する場合にはprint()メソッドは必ず実体を定義する必要があります。
			cout << "Child1::print()" << endl;
		}
} obj1;

class Child2 : public Parent {
	public:
		void print(){                              // Parentクラスを継承する場合にはprint()メソッドは必ず実体を定義する必要があります。
			cout << "Child2::print()" << endl;
		}
} obj2;

int main(){
	Parent *po1 = &obj1, *po2 = &obj2;
	po1->print();
	po2->print();
	return 0;

}
