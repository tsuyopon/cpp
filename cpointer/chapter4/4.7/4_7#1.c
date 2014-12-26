#include<stdio.h>

int main(){

	int matrix[2][5] = {{1,2,3,4,5},{6,7,8,9,10}};

	// 配列に対するポインタは次のように宣言することができます。
	int (*pmatrix)[5] = matrix;

	int i, j;
	for(i = 0; i < 2; i++){
		// 配列のポインタを出力
		printf("Address: %p\n", pmatrix[i]); 
		for(j = 0; j < 5; j++){
			// Addressの表示部分に着目すること
			// pmatrix[i] + j によりmatrix[i][j]の要素に対してアクセスすることができます。
			printf("matrix[%d][%d] Address: %p, %p, %p Value: %d\n", i, j, pmatrix[i]+j, matrix[i]+j, &matrix[i][j], matrix[i][j]);
		}
	}
	return 0;
}
