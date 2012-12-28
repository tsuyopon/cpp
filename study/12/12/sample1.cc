#include <iostream>
using namespace std;

#define ARRAY_SIZE(array) (sizeof (array) / sizeof *(array))

int main(){
	int n[100];
	cout << ARRAY_SIZE(n) << endl;
}
