#include<stdio.h>

int returnValue(){
	return 100;
}

int computeSqure(int a, int b){
	return a*b;
}

void main(){
	int tmp, tmp2;
	tmp = returnValue();
	printf("returnValue=%d\n", tmp);
	tmp2 = computeSqure(100, 5);
	printf("computeSqure=%d\n", tmp2);
	return;
}

