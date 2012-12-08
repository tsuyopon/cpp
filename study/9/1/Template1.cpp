#include <iostream>
using namespace std;

template <typename TYPE> TYPE Abs(TYPE a){
	return a < 0 ? -a : a;
}

int main(){
	cout << Abs(-10) << endl;
	cout << Abs(-0.89) << endl;
}
