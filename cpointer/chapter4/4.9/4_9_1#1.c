//
// 非連続となる可能性のある多次元配列メモリ割当について
//
#include<stdio.h>
#include<stdlib.h>

int main(){

	// matrix[2][5]の2次元配列のメモリ割当を動的に行う
	int rows = 2;
	int columns = 5;
	int i, j;

	//int型の２次元配列**matrixのrowsをmallocによって割り当てる
	int **matrix = (int **)malloc(rows*sizeof(int *));

	//int型の２次元配列**matrixのcolumnsをmallocによって割り当てる
	for(i = 0; i < rows; i++){
		matrix[i] = (int *)malloc(columns*sizeof(int));
	}

	// 上記のように割当を行うと、非連続となるメモリアドレスとなりえることがあります。
	// どのようなメモリ割当となるかは、ヒープマネージャーとその時のヒープ状態に依存します。
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("matrix[%d][%d]=%d, Address=%p\n", i, j, matrix[i][j], &matrix[i][j]);
		}
		printf("\n");
	}
}
