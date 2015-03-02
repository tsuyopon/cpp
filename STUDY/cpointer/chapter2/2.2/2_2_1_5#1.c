#include<stdio.h>
#include<stdlib.h>

int main(){

	// 静的変数
//	static int *pi = (int*)malloc(sizeof(int));

	// 大域変数
	static int *pi;
	pi = (int*)malloc(sizeof(int));
	free(pi);
}
