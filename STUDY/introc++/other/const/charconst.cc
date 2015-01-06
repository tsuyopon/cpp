#include <iostream>
#include <cstring>
using namespace std;

int main(){
	char aaa[] = "AAA";
	char bbb[] = "BBB";

	char* const pointer = aaa;  // char* const

	pointer[1] = 'c';  // compile ok
//	*pointer = 'd';    // compile ok
//	*pointer = 'ddd';  // compile error
//	pointer = bbb;     // compile error

	cout << pointer << endl;
}
