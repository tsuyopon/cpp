#include<iostream>
using namespace std;

/*
 *  多重継承について
 *    (A -> B-1,B-2 -> Cとなる並列的継承の場合)
 */

class GrandParent {
	public:
		GrandParent(){
			cout << "GrandParent" << endl;
		}
};

class Parent : public GrandParent {
	public:
		Parent(){
			cout << "Parent" << endl;
		}
};

class Parent2 : public GrandParent {
	public:
		Parent2(){
			cout << "Parent2" << endl;
		}
};

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
