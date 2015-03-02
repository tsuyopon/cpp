#include<iostream>
using namespace std;

bool Input(double& value){
	cout << "Input number > " << flush;
	value = 0;
	cin >> value;
	return value != 0;
}

int main(){
	double a, b;

	// (1) Input(a)の際に0を入力値として与えるとInput(b)が実行されることがなくなります。これをShortCircuitと呼びます
	while(Input(a) && Input(b)){
		cout << "a / b = " << (a / b) << endl;
		cout << "b / a = " << (b / a) << endl;
	}
}
