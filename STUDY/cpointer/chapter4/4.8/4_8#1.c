//
// 多次元配列を関数に渡すプログラム
//
#include<stdio.h>

// "void display2DArray(int (*arr)[5], int rows) 、ネ、、、ヲキチシー、ヌ、祕K
void display2DArray(int arr[][5], int rows){
	int i, j;
	for(i = 0; i < rows; i++){
		for(j = 0; j < 5; j++){
			printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
}

void main(){
	int matrix[2][5] = {
		{1,2,3,4,5},
		{6,7,8,9,10}
	};

	display2DArray(matrix, 2);
}

