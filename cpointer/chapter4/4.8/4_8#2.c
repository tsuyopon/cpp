//
// 多次元配列を関数に渡すプログラム
//
#include<stdio.h>

// サイズの異なる行列に何度も呼び出される際などに利用できる関数
void display2DArrayUnknownSize(int *arr, int rows, int cols){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < 5; j++){
			// arrは2次元配列をさすポインタとして宣言されていないので "arr[i][j]" といった記述はできません。
			printf("%d\t", *(arr + (i*cols) + j));
		}
		printf("\n");
	}
}

void main(){

	int matrix[2][5] = {
		{1,2,3,4,5},
		{6,7,8,9,10}
	};

	display2DArrayUnknownSize(&matrix[0][0], 2, 5);

	// 以下のようにして呼び出すとincompatible pointerの警告がでます。
	// これは、&matrix[0][0]がintへのポインタですが、matrixはint配列のポインタを表しているからです。
	//display2DArrayUnknownSize(matrix, 2, 5);

}

