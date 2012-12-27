#include<iostream>
using namespace std;

int main(){
	int a, b;
	cout << "Input Two Number > " << flush;
	cin >> a >> b;

	cout << "Bigest value is " << (a > b ? a : b) << endl;

}
