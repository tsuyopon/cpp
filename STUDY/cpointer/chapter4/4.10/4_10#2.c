//
// 3次元配列の初期化
//
#include<stdio.h>

int main(){
	int (*(arr1[])) = {
		(int[]){0, 1, 2},
		(int[]){3, 4, 5},
		(int[]){6, 7, 8},
	};

	int i, j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			printf("arr1[%d][%d] Address: %p Value: %d\n", i, j, &arr1[i][j], arr1[i][j]);
		}
		printf("\n");
	}


}
