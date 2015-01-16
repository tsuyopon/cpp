#include<iostream>
using namespace std;

/*
 * 仮想関数について
 *   ※　仮想関数では、デストラクタは利用できません(∵デストラクタの場合、派生クラス側から崩壊するという原則が存在するため)
 */
class Parent {
	public:
		virtual void print(){                        // (1) print()関数   virtualキーワードは基本クラスで指定します。
			cout << "Parent::print()" << endl;
		}
} pobj;

class Child1 : public Parent {
	public:
		void print(){                                // (2) print()関数
			cout << "Child1::print()" << endl;
		}
} cobj1;

class Child2 : public Parent {
	public:
		void print(){                                // (3) print()関数
			cout << "Child2::print()" << endl;
		}
} cobj2;

int main(){
	// (1)でvirtualを指定しない場合には、全てParent::print()が表示されることになります。
	Parent *po1 = &pobj, *po2 = &cobj1, *po3 = &cobj2;
	po1->print();
	po2->print();
	po3->print();


	// 実行時バインディングの例
	Parent *po;
	unsigned char ch;
	cout << "Enter y/n?  >";
	cin >> ch;

	if( ch == 'y' ){
		po = &pobj;
	} else {
		po = &cobj1;
	}
	po->print();           // 入力された内容に応じて出力されるクラスが異なります。実行時バインディングと呼びます。コンパイル時バインディングとは対になる用語です。
	return 0;
}
