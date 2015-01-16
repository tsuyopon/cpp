#include<iostream>
using namespace std;

/*
 * 継承をしている場合のコンストラクタ、デストラクタについて
 */
class Parent {
	public:
		Parent(){
			cout << "Parent Class Constructor" << endl;
		}

		~Parent(){
			cout << "Parent Class Destructor" << endl;
		}
};

class Child : public Parent {
	public:
		Child(){
			cout << "Child Class Constructor" << endl;
		}
		~Child(){
			cout << "Child Class Destructor" << endl;
		}
} obj;

int main()
{
	// 出力されるコンストラクタ、デストラクタの順序に注意すること
	return 0;
}
