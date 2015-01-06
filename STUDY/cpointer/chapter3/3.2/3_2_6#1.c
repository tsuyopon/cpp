#include<stdio.h>
#include<stdlib.h>

// 引数にint配列ポインタを渡すようにしています。
int* allocateArray(int *arr, int size, int value){

	// mallocは割当できない場合にはNULLを返却するので、NULLをチェックするのはよい習慣です。
	if(arr != NULL){
		int i;
		for(i = 0; i < size; i++){
			arr[i] = value;
		}
	}
	return arr;
}

int main(){

	int i;
	int* vector = (int*)malloc(5*sizeof(int));
	allocateArray(vector, 5, 45);
	for(i = 0; i < 5; i++){
		printf("%d\n", vector[i]);
	}
	free(vector);
	return 0;
}
