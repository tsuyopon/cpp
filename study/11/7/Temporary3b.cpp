#include <iostream>
using namespace std;

int Abs(const int& a){
	return a < 0 ? -a : a;
}

int main(){
	cout << Abs(-10) << endl;
}
