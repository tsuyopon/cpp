#include<iostream>
using namespace std;

class Base {
	public:
		virtual void paint() = 0;    // 純粋仮想関数と呼ぶ。これを継承するクラスは必ずこの関数の再定義が必要となる。
};

class Sub1 : public Base {
	public:
		void paint() {cout << "Sub1 paint" << endl;}
} obj1;

class Sub2 : public Base {
	public:
		void paint() {cout << "Sub2 paint" << endl;}
} obj2;

int main(){
	Base *po1 = &obj1, *po2 = &obj2;
	po1->paint();
	po2->paint();
	return 0;
}
