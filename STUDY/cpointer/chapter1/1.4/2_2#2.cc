#include<stdio.h>

int main(){

	int num1;
	int *const cpi1 = &num1;

	// アドレスの向き先はconstで固定ですが、向き先(num1)自体の値を変更することはできます。
	num1 = 100;
	printf("cpi1_value=%d, num1_value=%d\n", *cpi1, num1);

	*cpi1 = 99;
	printf("cpi1_value=%d, num1_value=%d\n", *cpi1, num1);

}
