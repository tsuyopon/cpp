#include<stdio.h>

// Eの型定義宣言に加えて変数宣言も同時に行います。このときa1の型はEです。
enum E {E1,E2} a1;  //  "enum E{E1, E2} a1"でもOK

int main(){

	// a1はすでに宣言されているので定義は不要
	a1 = E1;

	// 2つめの変数を定義することもできる。
	enum E a2;
	a2 = E2;

	printf("a1 value=%d, a2 value=%d\n", a1, a2);
	return 0;

}
