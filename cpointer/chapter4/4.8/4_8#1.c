//
// ‘½ŸŒ³”z—ñ‚ğŠÖ”‚É“n‚·ƒvƒƒOƒ‰ƒ€
//
#include<stdio.h>

// "void display2DArray(int (*arr)[5], int rows) ¤È¤¤¤¦·Á¼°¤Ç¤âOK
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

