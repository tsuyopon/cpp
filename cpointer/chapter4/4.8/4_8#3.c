//
// 3次元配列を表示するためのプログラム
//
#include<stdio.h>

void display3DArray(int (*arr)[2][4], int rows){
	int i, j, k;
	for(i = 0; i < rows; i++){
		for(j = 0; j < 2; j++){
			printf("{");
			for(k = 0; k < 4; k++){
				printf("%d ", arr[i][j][k]);
			}
			printf("}");
		}
		printf("\n");
	}
}

void main(){
	int arr3d[3][2][4] = {
		{{1,2,3,4},{5,6,7,8}},
		{{9,10,11,12},{13,14,15,16}},
		{{17,18,19,20},{21,22,23,24}}
	};
	display3DArray(arr3d, 3);

}
