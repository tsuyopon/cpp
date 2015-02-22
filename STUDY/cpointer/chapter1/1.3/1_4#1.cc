// ポインタからポインタを引く
#include<stdio.h>

int main(){
	int vector[] = {28, 41, 7};
	int *p0 = vector;
	int *p1 = vector+1;
	int *p2 = vector+2;

	printf("p2-p0: %ld\n", p2-p0);
	printf("p2-p1: %ld\n", p2-p1);
	printf("p0-p1: %ld\n", p0-p1);

}
