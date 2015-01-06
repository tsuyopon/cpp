#include<iostream>
#include<cstdarg>
using namespace std;

int Sum(int first, ...) {     // ...とすることによって可変長引数を定義できる
	int sum = 0;
	va_list args;
	va_start(args, first);
	for(int n = first; n != 0; n = va_arg(args, int)){
		sum += n;
	}
	va_end(args);
	return sum;
}

int main(){
	cout << Sum(0) << ' '
		<< Sum(1, 0) << ' '
		<< Sum(7, 3, 0) << ' '
		<< Sum(1, 2, 3, 4, 5, 0) << endl;
}

