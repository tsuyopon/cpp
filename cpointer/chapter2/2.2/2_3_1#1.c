#include<stdio.h>
#include<stdlib.h>

int main(){
	int *pi = (int*)malloc(sizeof(int));
	free(pi);
	pi = NULL;    // 誤ってそのポインタを使ってしまう可能性があるので明示的にNULLにしておく手法がある。
}
