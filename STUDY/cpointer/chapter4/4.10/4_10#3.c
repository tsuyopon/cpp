//
// 4_10#2.cを改良してジャグ配列を宣言
//
#include<stdio.h>

int main(){

	// 列のサイズが各々異なるジャグ配列を宣言します。
	int (*(arr2[])) = {
		(int[]){0, 1, 2, 3},
		(int[]){4, 5},
		(int[]){6, 7, 8},
	};

	// 各行は異なる値で構成されているので3つのforループが必要です。
	int i, j;

	int row = 0;
	int column = 4;
	for(i = 0; i < column; i++){
		printf("layer1[%d][%d] Address: %p Value: %d\n", row, i, &arr2[row][i], arr2[row][i]);
	}
	printf("\n");

	row = 1;
	column = 2;
	for(i = 0; i < column; i++){
		printf("layer1[%d][%d] Address: %p Value: %d\n", row, i, &arr2[row][i], arr2[row][i]);
	}
	printf("\n");

	row = 2;
	column = 3;
	for(i = 0; i < column; i++){
		printf("layer1[%d][%d] Address: %p Value: %d\n", row, i, &arr2[row][i], arr2[row][i]);
	}
	printf("\n");
}
