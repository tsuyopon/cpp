#include<stdio.h>
#include<stdlib.h>

int main(){
	int *pi = (int*)malloc(sizeof(int));

	// 要求されたメモリを割り当てられない場合にはNULLポインタであるかどうかを判別する習慣をつけましょう。
	if(pi != NULL){
		printf("Pointer is valid\n");
	} else {
		printf("Pointer is invalid\n");
	}
	free(pi);
}
