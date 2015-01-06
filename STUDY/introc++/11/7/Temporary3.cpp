#include <iostream>
using namespace std;

int Abs(const int& a){
	return a < 0 ? -a : a;
}

int main(){
	int n = -10;
	cout << Abs(n) << endl;
}
