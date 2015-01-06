#include <iostream>
using namespace std;

int main(){

	int n[2][3] = {
		{100, 101, 102},
		{200, 201, 202},
	};

	int m[][5] = {
		{11, 12, 13, 14, 15},
		{21, 22, 23, 24, 25},
		{31, 32, 33, 34, 35},
	};

	cout << "*n[0]: " << *n[0] << endl;
	cout << "*n[1]: " << *n[1] << endl;
	cout << "n[1][2]: " << n[1][2] << endl;
	cout << "*m[0]: " << *m[0] << endl;
	cout << "*m[1]: " << *m[1] << endl;
	cout << "*m[2]: " << *m[2] << endl;
	cout << "m[2][2]: " << m[2][2] << endl;
}
