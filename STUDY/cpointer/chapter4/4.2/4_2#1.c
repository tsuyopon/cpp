//
// 配列とアドレスの関係性について理解するプログラムです。
//
#include<stdio.h>

int main(){
	int vector[5] = {1,2,3,4,5};
	int *pv = vector;

	printf(" vector=%p\n", vector);
	printf("     pv=%p, &vector[0]=%p\n", pv,   &vector[0] );
	printf("   pv+1=%p, &vector[1]=%p\n", pv+1, &vector[1] );
	printf("   pv+2=%p, &vector[2]=%p\n", pv+2, &vector[2] );
	printf("   pv+3=%p, &vector[3]=%p\n", pv+3, &vector[3] );
	printf("   pv+4=%p, &vector[4]=%p\n", pv+4, &vector[4] );
	printf("   pv+5=%p, &vector[5]=%p\n", pv+5, &vector[5] );
}
