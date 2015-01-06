//
// 関数ポインタのキャストを利用してみます。
// オーバーロードを利用しているのでC++のg++でコンパイルが必要です。
// 
#include<stdio.h>

typedef int (*fptrToSingleInt)(int);
typedef int (*fptrToTwoInts)(int, int);

int add(int num1){
	return num1;
}

int add(int num1, int num2){
	return num1 + num2;
}

int main(){

	fptrToTwoInts fptrFirst = add;
	printf("fptrToTwoInts: %d\n", fptrFirst(5, 6));
	fptrToSingleInt fptrSecond = (fptrToSingleInt)fptrFirst;
	fptrFirst = (fptrToTwoInts)fptrSecond;
	printf("fptrToTwoInts: %d\n", fptrFirst(5, 6));
	return 0;
}
