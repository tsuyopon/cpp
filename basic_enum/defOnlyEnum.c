#include<stdio.h>

// enumを宣言している
enum {E1,E2};

int main(){
	// enumで宣言したenumの変数利用を宣言する。ただし、宣言するのがちょっと面倒だ。
	enum{E1,E2} a1;

	// 2つ目の変数を定義しようとするとエラーとなる(コメントアウトしている)
	//enum{E1,E2} a2;

	a1 = E1;
	printf("value=%d\n", a1);
	return 0;
}
