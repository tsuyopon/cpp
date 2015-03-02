#include<stdio.h>
#include<stdlib.h>

int main(){

	// 以下の例は20(5*4)バイトのメモリ割当を行い、内容を0でクリアします。
	// calloc関数はメモリ割当と内容のクリアを行う関数です。
	int *pi = (int*)calloc(5, sizeof(int));
	free(pi);

	// なお、malloc関数とmemset関数を組み合わせることでcallocと同一のことを実現することができます。
	// int *pi = malloc(5*sizeof(int));
	// memset(pi, 0, 5*sizeof(int));
}
