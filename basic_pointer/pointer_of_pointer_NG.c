#include<stdio.h>
#include<stdlib.h>

/* WARNING */
/* このプログラムは正しく動作しません */

// 1. mainからポインタの""アドレスのコピー""がarrに渡されます。例えば0xfff1などと仮定する。
// 2. mallocから生成されたアドレスをarrとして代入する。これを0xeee1などと仮定する。
// 3. arr[i]にすることによってmallocで生成されたヒープ領域にデータを格納している。
// 4. arrは2の操作で0xfff1から0xeee1に変わってしまった。しかし、関数のアドレスがallocateArrayにコピーされただけなので、関数から制御が戻ってもmain側の&vectorで渡しているアドレスは0xfff1のままとなる。
// 5. 実はmallocで生成された領域のアドレスを指し示すアドレスはわからなくなってしまったのでメモリリークを起こします。
//
// このため、アドレスを渡したいのであればポインタのポインタを渡します。これはpinter_of_pointer_OK.cを見てください。


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
