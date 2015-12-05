#include<iostream>
using namespace std;

// C++11ではクラスの初期化を定義することができるようになりました。
class Test {
	int i;
	public:
		Test(int ia) : i(ia) { cout << i << endl; }
		Test() : Test(123) { cout << "set init 123" << endl; }
};

int main(void){
	Test test;
	return 0;
}
