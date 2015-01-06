#include <iostream>
using namespace std;

#define SIZE 255

int main(){
	int *p1;
	int *p2;

	p1 = new int;       // allocate 1 int
	p2 = new int[SIZE]; // allocate SIZE int

	*p1 = 1000;
	cout << *p1 << endl;

	// free
	delete p1;          // noarray
	delete [] p2;       // array

}
