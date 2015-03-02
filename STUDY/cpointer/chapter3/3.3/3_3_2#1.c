// 
// 関数ポインタを宣言して、利用する最もシンプルなサンプルです。
//
#include<stdio.h>

// 関数ポインタ宣言。関数ポインタの変数名はfptr1としてこの時点で定義されます。
int (*fptr1)(int);

int square(int num){
	return num*num;
}

int twofold(int num){
	return 2*num;
}

int main(){
	int n = 5;

	// 関数ポインタを利用してsquare関数を呼び出します。 &squareとしてもよいですが、つける必要はありません。
	fptr1 = square;
	printf("%d squared is %d\n", n, fptr1(n));

	// 関数ポインタを再利用してtwofold関数を呼び出します。
	fptr1 = twofold;
	printf("%d twofold is %d\n", n, fptr1(n));
	return 0;
}
