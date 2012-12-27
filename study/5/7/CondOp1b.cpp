#include<iostream>
using namespace std;

int main(){
	int a, b;
	cout << "Input Two Number > " << flush;
	cin >> a >> b;

	if(a > b){
		cout << "biggest value is: " << a << endl;
	} else {
		cout << "biggest value is: " << b << endl;
	}
}
