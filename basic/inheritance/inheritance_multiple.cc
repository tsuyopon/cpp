#include<iostream>
using namespace std;

/*
 *  多重継承について
 *    (A -> B -> Cとなる直列的継承の場合)
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

class Child : public Parent {
	public:
		Child(){
			cout << "Child" << endl;
		}
};

int main(){
	Child obj;
	return 0;
}
