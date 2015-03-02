#include<stdio.h>
#include<stdlib.h>

int main(){

	// mallocの戻り値は「void *」型(つまり何の型のアドレスにも変換できる)なので適切に(int*)型にキャストしてあげる必要があります。
	// sizeof演算子によりint型のサイズを算出しているので実行環境による動作の影響を気にすることがなくなります。
	int *pi = (int*)malloc(sizeof(int));
	*pi = 5;
	printf("*pi: %d\n", *pi);
	free(pi);
}
