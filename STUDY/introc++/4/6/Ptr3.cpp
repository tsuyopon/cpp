#include<iostream>
using namespace std;

int main(){
	int n[4];
	int* p = n;

	cout << "p     : " << (size_t)p     << endl;
	cout << "&n[0] : " << (size_t)&n[0] << endl;

	p += 2;
	cout << "p     : " << (size_t)p     << endl;
	cout << "&n[2] : " << (size_t)&n[2] << endl;

}
