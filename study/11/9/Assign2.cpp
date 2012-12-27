#include<iostream>
using namespace std;

int main(){
	int a, b;

	b = 0;
	a = (++b);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl << endl;

	b = 0;
	a = (b++);
	cout << "a = " << a << endl;
	cout << "b = " << b << endl << endl;

}
