/*
 * WARNING: This Program can not compile.
 */
#include <iostream>
#include <string>
using namespace std;

template <typename TYPE> TYPE Abs(TYPE a){
	return a < 0 ? -a : a;                    // if "a" type is string, this logic can not execute.
}

int main(){
	string str = "hoge";
	cout << Abs(str) << endl;
}
