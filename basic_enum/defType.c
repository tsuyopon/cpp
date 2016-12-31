#include<stdio.h>

enum E {E1,E2};

int main(){
	// "enum {E1,E2};"の定義だと「enum {E1,E2} a1;」と記述しなければならない
	enum E a1;
	enum E a2;       // notypedef1.cやnotypedef2.cと異なり複数個宣言することができる。
	a1 = E1;
	a2 = E2;
	printf("a1 value=%d, a2 value=%d\n", a1, a2);
	return 0;
}
