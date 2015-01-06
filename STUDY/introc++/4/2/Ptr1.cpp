#include <iostream>
using namespace std;

int main(){
	char a;
	char* p;

	p = &a;
	cout << " p = " << (size_t)p  << endl;
	cout << "&a = " << (size_t)&a << endl;
}
