#include<iostream>
using namespace std;

/*
 *  フレンドクラスの使用方法について
 */

class Parent {
	private:
		int years;
		int month;

	public:
		void set(int y, int m){
			years = y;
			month = m;
		}

	friend class Child;               // フレンドクラスの宣言

};

class Child {
	public:
		void display(Parent obj){
			cout << "years:" << obj.years << endl;   // フレンド関数を利用してParentクラスのprivateにアクセス
			cout << "month:" << obj.month << endl;   // フレンド関数を利用してParentクラスのprivateにアクセス
		}
};

int main(){

	class Parent pobj;
	pobj.set(2011, 6);

	class Child cobj;
	cobj.display(pobj);

	return 0;
}
