#include<stdio.h>
#include<stdlib.h>

/* WARNING */
// このプログラムは正しく動作しません。


// ポインタのポインタではなく*arrをパラメータ指定に変更しました。
// arrはallocateArray()内でコピーされているだけなので、main側に制御が戻った際にarr[n]を指し示すポインタが消滅してしまいます。
void allocateArray(int *arr, int size, int value){

	arr = (int*)malloc(size*sizeof(int));
	if(arr != NULL){
		int i;
		for(i = 0; i < size; i++){
			arr[i] = value;
		}
	}
}

int main(){

	int i;
	int *vector = NULL;
	allocateArray(vector, 5, 45);
	for(i = 0; i < 5; i++){
		printf("%d\n", vector[i]);
	}
	free(vector);
	return 0;
}
