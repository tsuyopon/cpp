//
// typedefを利用した関数ポインタ宣言
//
#include<stdio.h>

// 関数ポインタとtypedef宣言は相性が良く、以下のように利用されます。
// 通常のtypedefとは異なるので誤解しないようにしましょう。例えばtypedef int size_t みたいな置き換えとは全く違う概念です。通常のtypedefとは異なるので誤解しないようにしましょう。
// int (*funcptr)(int)は(*funcptr)(int)という関数ポインタはint型の戻り値を返すということを意味しています。
// int (*funcptr)(int)は(*funcptr)(int)という関数ポインタはint型の戻り値を返すということを意味しています。
typedef int (*funcptr)(int);

int square(int num){
	return num*num;
}

int main(){

	funcptr fptr1;
	fptr1 = square;
	int n = 5;
	printf("%d squared is %d\n", n, fptr1(n));

	return 0;
}
