#include<iostream>
using namespace std;

/*
 *  多重継承について
 *    (並列的継承の問題点を解決する仮想基本クラスについて)
 *    inheritance_multiple3.ccでは、GrandParentが複数回呼ばれますが、仮想基本クラスを呼ぶとそのようなことを回避できます。
 */

class GrandParent {
	public:
		GrandParent(){
			cout << "GrandParent" << endl;
		}
};

class Parent : virtual public GrandParent {      // 仮想基本クラスvirtualが指定されています。public指定です。
	public:
		Parent(){
			cout << "Parent" << endl;
		}
};

class Parent2 : virtual private GrandParent {     // 仮想基本クラスvirtualが指定されています。private指定です。
	public:
		Parent2(){
			cout << "Parent2" << endl;
		}
};

/*
 *  下記の場合には、
 *      Parentクラスは、publicでGrandParentを継承しています。
 *      Parent2クラスは、privateでGrandParentを継承しています。
 *      ChildからGrandParentクラスにアクセスする場合には最もオープンな制御(つまり、この場合はpublic)をとります。
 */
class Child : public Parent, public Parent2 {    // 2つを継承していることに着目
	public:
		Child(){
			cout << "Child" << endl;
		}
};

int main(){
	Child obj;
	return 0;
}
