//
// 連続した多次元配列のメモリ割当の方法
//
#include<stdio.h>
#include<stdlib.h>

int main(){
	int rows = 2;
	int columns = 5;
	int i, j;

	// 連続した領域とするためにrows * columnsとしていることに注意
	int **matrix = (int **)malloc(rows * columns * sizeof(int *));
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			// 本来であれば2次元配列があっても1次元の領域としてメモり割当を行っているので、配列のインデックスは使用できませんので
			// 以下の様に手動で計算をする必要があります。
			*(matrix + (i*columns) + j) = i * columns + j;
		}
	}

	// 出力をする
	for(i = 0; i < rows; i++){
		for(j = 0; j < columns; j++){
			printf("%d\t", *(matrix + (i*columns) + j ));
		}
		printf("\n");
	}

}
