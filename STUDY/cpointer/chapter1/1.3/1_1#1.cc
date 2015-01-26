#include<stdio.h>

int main(){
	int vector[] = {28, 41, 7};
	int *pi = vector;

	printf("%d\n", *pi);
	pi += 1;
	printf("%d\n", *pi);
	pi += 1;
	printf("%d\n", *pi);
}
