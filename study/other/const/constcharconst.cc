#include <iostream>
#include <cstring>
using namespace std;

int main(){
	char aaa[] = "AAA";
	char bbb[] = "BBB";

	const char* const pointer = aaa;  // const char* const

//	pointer[1] = 'c';  // compile error
//	*pointer = 'd';    // compile error
//	*pointer = 'ddd';  // compile error
//	pointer = bbb;     // compile error

	cout << pointer << endl;
}
