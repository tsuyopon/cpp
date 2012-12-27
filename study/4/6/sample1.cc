#include<iostream>
using namespace std;

int main(){
	int n[4];

	cout << "&n[3] - &n[0] : " << (size_t)(&n[3] - &n[0]) << endl;
	cout << "&n[3] - &n[1] : " << (size_t)(&n[3] - &n[1]) << endl;
	cout << "&n[3] - &n[2] : " << (size_t)(&n[3] - &n[2]) << endl;
	cout << "&n[3] - &n[3] : " << (size_t)(&n[3] - &n[3]) << endl;
	cout << "&n[2] - &n[0] : " << (size_t)(&n[2] - &n[0]) << endl;
	cout << "&n[2] - &n[1] : " << (size_t)(&n[2] - &n[1]) << endl;
	cout << "&n[2] - &n[2] : " << (size_t)(&n[2] - &n[2]) << endl;
	cout << "&n[2] - &n[3] : " << (size_t)(&n[2] - &n[3]) << endl;
	cout << "&n[1] - &n[0] : " << (size_t)(&n[1] - &n[0]) << endl;
	cout << "&n[1] - &n[1] : " << (size_t)(&n[1] - &n[1]) << endl;
	cout << "&n[1] - &n[2] : " << (size_t)(&n[1] - &n[2]) << endl;
	cout << "&n[1] - &n[3] : " << (size_t)(&n[1] - &n[3]) << endl;

}
