#include <iostream>
using namespace std;

template <typename TYPE_A, typename TYPE_B> void Show (TYPE_A a, TYPE_B b){
	cout << "a:" << a << ", b:" << b << endl;
}

int main(){
	Show(100, 0.1);  // 1st arg: int, 2nd arg: double
	Show(0.1, 100);  // 1st arg: double, 2nd arg: int
	Show(100, 100);  // Both Int Type
}
