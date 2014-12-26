#include<stdio.h>
#include<stdlib.h>

// [重要] ポインタを関数に渡すと関数へはポインタの値が渡されることになります。
// このため、アドレスを渡したいのであればポインタのポインタを渡します。それによって*arrとするとarrのアドレス値を指し示すようになります。
//
// 以下の例では戻りをvoidにして、ポインタの値を関数内部で操作するのでポインタのポインタを渡しています。
void allocateArray(int **arr, int size, int value){

	*arr = (int*)malloc(size*sizeof(int));
	if(*arr != NULL){
		int i;
		for(i = 0; i < size; i++){
			*(*arr+i) = value;
		}
	}
}

int main(){

	int i;
	int *vector = NULL;
	allocateArray(&vector, 5, 45);
	for(i = 0; i < 5; i++){
		printf("%d\n", vector[i]);
	}
	free(vector);
	return 0;
}
