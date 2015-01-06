#include <iostream>
#include <algorithm>
using namespace std;

// 1. CheckAddress()
void CheckAddress_Sub();
void CheckAddress_Sub2();

void CheckAddress(){

	cout << "1. Check if address is constant." << endl;

	CheckAddress_Sub();
	CheckAddress_Sub2();
	CheckAddress_Sub();
}

void CheckAddress_Sub(){

	cout << "CheckAddress_Sub START" << endl;
	static int a;
	int b;
	cout << "&a = " << (size_t)&a << endl
		 << "&b = " << (size_t)&b << endl;
}

void CheckAddress_Sub2(){
	cout << "CheckAddress_Sub2 START" << endl;
	CheckAddress_Sub();
}

// 2. CheckInitOnce()
void CheckInitOnce_Sub();

void CheckInitOnce(){
	cout << endl << "2. Check if initialization is executed" << endl;
	CheckInitOnce_Sub();
	CheckInitOnce_Sub();
}

void CheckInitOnce_Sub(){
	static int a = 3;
	int b = 3;
	cout << "a = " << a << endl
		 << "b = " << b << endl;

	++a;
	++b;
}

// 3. CheckZeroInit()
void CheckZeroInit_Sub();
void CheckZeroInit_Sub2();

void CheckZeroInit(){
	cout << endl << "3. Check if zero initialization is execute." << endl;
	CheckZeroInit_Sub();
	CheckZeroInit_Sub2();
}

void CheckZeroInit_Sub(){
	static int a, b, c, d;
	cout << a << ',' << b << ',' << c << ',' << d << endl;
}

void CheckZeroInit_Sub2(){
	int a, b, c, d;
	cout << a << ',' << b << ',' << c << ',' << d << endl;
}

// 4. CheckInvariant()
void CheckInvariant_Sub(int*& pa, int*& pb);
void CheckInvariant_Sub2();

void CheckInvariant(){
	cout << endl << "4. Check if value is in warranty" << endl;
	int *pa, *pb;
	CheckInvariant_Sub(pa, pb);
	CheckInvariant_Sub2();
	cout << "*pa = " << *pa << endl
		 << "*pb = " << *pb << endl;
}

void CheckInvariant_Sub(int*& pa, int*& pb){
	static int a = 9;
	int b = 9;
	pa = &a;
	pb = &b;
}


void CheckInvariant_Sub2(){
	int dummy[100];
	fill_n(dummy, 100, 0);
}

//////////////////////////
// MAIN SECTION
//////////////////////////
int main(){
	CheckAddress();     // 1.
	CheckInitOnce();    // 2.
	CheckZeroInit();    // 3.
	CheckInvariant();   // 4.
}
