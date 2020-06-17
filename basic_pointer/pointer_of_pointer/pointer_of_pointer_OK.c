#include<stdio.h>
#include<stdlib.h>

// ポインターのポインターを渡すことでpointer_of_pointer_NG.cの問題を解決できます。
// つまり次のことができます。
//   mallocによって生成されたアドレスを保存できる。
//   そのmallocによって確保されたヒープ領域にデータを格納できる。
// つまり、２次元のデータ保存を行いたい場合にポインタのポインタを使うことになります。

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
