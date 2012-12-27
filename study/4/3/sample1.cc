#include <iostream>
using namespace std;

int main(){
	int a;
	int& r = a;

	a = 0;
	cout << "a = " << a << endl;
	cout << "r = " << r << endl;

	r = 5;
	cout << "a = " << a << endl;
	cout << "r = " << r << endl;
}
