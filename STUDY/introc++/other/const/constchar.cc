#include <iostream>
using namespace std;

int main(){
	char aaa[] = "AAA";
	char bbb[] = "BBB";
	const char* pointer = aaa;    // const char*

//	pointer[1] = 'c';  // compile error
//	pointer = bbb;     // compile ok
//	*pointer = 'xxx';  // compile error

	cout << pointer << endl;
}
