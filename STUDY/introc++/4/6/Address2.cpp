#include<iostream>
using namespace std;

int main(){
	int n[5];

	cout << "&n[2]     = " << (size_t)&n[2]       << endl;
	cout << "&n[2] + 1 = " << (size_t)(&n[2] + 1) << endl;
	cout << "&n[3]     = " << (size_t)&n[3]       << endl;
}
