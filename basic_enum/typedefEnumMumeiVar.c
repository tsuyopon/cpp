#include<stdio.h>

// typedefの場合にはenum{E1,E2}をエイリアスEとして定義している。
// "enum E{E1,E2}"ではEという型を独自で定義したが、今回の場合はエイリアスにすぎないのでEで宣言された型名は無名を意味する。
typedef enum{E1,E2} E;

int main(){
	E a1;    // Eは実質"enum{E1,E2}"に置き換えられる。つまり、a1の型は無名となる。
	a1 = E1;

	// 2つめも定義することができる。
	E a2;
	a2 = E2;

	printf("a1 value=%d, a2 value=%d\n", a1, a2);
	return 0;
}
