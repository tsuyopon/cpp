#include <iostream>
using namespace std;

template <typename TYPE> size_t ArraySize(TYPE array[]){
	return sizeof array / sizeof *array;
}

int main(){
	int n[100];
	cout << ArraySize(n) << endl;
}
