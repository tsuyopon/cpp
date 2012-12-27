#include<iostream>
using namespace std;

int main(){
	int a = 0, b = 0;
	a = (b = 5);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl << endl;
	cout << "b = " << (b += 3) << endl << endl;
	cout << "b = " << b << endl << endl;

	(b = 1) += a;
	cout << "b = " << b << endl;
}
