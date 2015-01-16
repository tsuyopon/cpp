#include<iostream>
using namespace std;

/*
 *  多重継承について
 *    ( B-1,B-2 -> Cとなる並列的継承の場合)
 */

class Parent {
	public:
		Parent(){
			cout << "Parent" << endl;
		}
};

class Parent2 {
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
