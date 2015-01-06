#include<stdio.h>
#include<stdlib.h>

int main(){
	int* arr[5];
	int i;
	for(i=0; i<5; i++){
		arr[i] = (int*)malloc(sizeof(int));
		*arr[i] = i;
		// 以下の書き方でもOK
		//**(arr+i) = i;

		printf("%d\t", *arr[i]);
	}
	printf("\n");
}
