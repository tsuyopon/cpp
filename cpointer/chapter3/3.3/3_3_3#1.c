//
// 関数ポインタを引数に持つ関数について
//
#include<stdio.h>

int add(int num1, int num2){
	return num1 + num2;
}

int sub(int num1, int num2){
	return num1 - num2;
}

// 関数ポインタ宣言を行います。
typedef int (*fptrOperation)(int, int);

// compute関数は関数ポインタを引数として持っています。
// typedefを使っている利点はこのメソッドの宣言を簡略化してくれています。
// typedefを使わなければ int compute(int (*fptrOperation)(int, int) operation, int num1, int num2) となっていました。
int compute(fptrOperation operation, int num1, int num2){
	return operation(num1, num2);
}

int main(){
	// 関数ポインタを利用することによってcomputeという関数内でaddやsubといった関数の出し分けを行っています。
	printf("%d\n", compute(add, 5, 6));
	printf("%d\n", compute(sub, 5, 6));
}
